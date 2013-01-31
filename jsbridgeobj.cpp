#include "jsbridgeobj.h"
#include <QtGui>
#include <QDateTime>

JSBridgeObj::JSBridgeObj(QObject *parent) :
    QObject(parent)
{
}

void JSBridgeObj::setFrame(QWebFrame *fr){
    frame = fr;
}

/*========================================
           Calls from JavaScript
==========================================*/

int JSBridgeObj::launchApp(QString str){

    QString JSONdir = "Results";
    int exit = 1;
    QString jsonName = QDate::currentDate().toString("dd.MM.yyyy").append(".json");

    if(!QDir(JSONdir).exists()){
        QDir().mkdir(JSONdir);
    }

    QString filePath = QDir::currentPath() + "/" + JSONdir + "/" + jsonName;
    if (str.contains(".jar") && str.lastIndexOf(".jar") == str.size() - 4 )
    {
        exit =  QProcess::execute( "java", QStringList() << "-jar" << str << filePath);
    }
   // else if(str.contains(".jar") && str.lastIndexOf(".jar") == str.size() - 4){
   //     exit =  QProcess::execute( "java", QStringList() << "-jar" << str );
    //}
    else if (str.contains(".exe") && str.lastIndexOf(".exe") == str.size() - 4)
    {
       #if defined(Q_OS_MAC)
        exit =  QProcess::execute("mono",  QStringList() << str);


       #elif defined(Q_OS_WIN32)
        exit =  QProcess::execute(str, QStringList());
        #endif
    }
    if(exit == 0){
        QString js = fetchFile(filePath);
        QString esc_js = escapeJavascriptString(js);
        frame->evaluateJavaScript(QString("sendTestResults('%1')").arg(esc_js));
        QFile::remove(filePath);
    }

    return exit;
}

void JSBridgeObj::initiateDownload(QString fileUrl, QString Cat, QString Desc){
    DownloadManager *manager = new DownloadManager();
    manager->downloadFile(fileUrl, Cat, Desc);
    connect(manager,SIGNAL(downloadCallback(QString)),SLOT(JSCallback(QString)));
}

QString JSBridgeObj::fetchFile(QString filename){

    QFile file (filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString data = stream.readAll();
        file.close();

        return data;
    }

    return " ";
}


QVariant JSBridgeObj::uninstallApp(QString AppName, QString Category){

    QString dirName = QDir::currentPath() + "/" + "AppFolder" + "/" + Category + "/" + AppName + "App";

    bool r = removeDir(dirName);
    if(r){

        QFile file("update.json");

        if (file.open(QIODevice::ReadWrite)){

            QTextStream stream (&file);

            QFile fileTemp("updatetemp.json");
            fileTemp.open(QIODevice::WriteOnly);
            QTextStream streamTemp (&fileTemp);
            int counter = 0;
            while(!stream.atEnd()){

                QString lineTemp = stream.readLine();

                if(!lineTemp.contains(AppName) && !lineTemp.contains(Category)){
                    streamTemp << lineTemp << endl;
                }
                counter++;

            }

            file.close();
            QFile::remove("update.json");
            if(counter - 1 < 3){
                fileTemp.close();
                QFile::remove("updateTemp.json");
            }
            else{
                fileTemp.rename("update.json");
                fileTemp.close();
            }
        }
        return "true";
    }

    return "false";
}

void JSBridgeObj::updateFile(QString fileName, QString data){

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream stream (&file);
        stream << data;
        file.close();
    }

}

QVariant JSBridgeObj::appExists(QString AppName, QString Category){

    QFile file("update.json");

    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);

        while(!stream.atEnd()){
            QString line = stream.readLine();
            if(line.contains(AppName) && line.contains(Category)){
                file.close();
                return true;
            }
        }
    }
    return false;
}

bool JSBridgeObj::dependancyCheck(QString dep){

    QProcess *proc = new QProcess();
    proc->start(dep, QStringList());

    if (!proc->waitForFinished())
        return false;
    QString procOutput = proc->readAllStandardOutput();

    if(procOutput.isNull()){
        return false;
    }
    else return true;
    return false;
}

QString JSBridgeObj::bootChecks(){

    QString msg;
    if(!dependancyCheck("java")){
        msg.append("     Java<br/>");
    }
#if defined(Q_OS_MAC)
    if(!dependancyCheck("mono")){
        msg.append("     Mono<br/>");
    }
#endif
    return msg;
}

/*===============================================
                 Javascript callback
=================================================*/

void JSBridgeObj::JSCallback(QString callback){
    frame->evaluateJavaScript(callback);
}



void JSBridgeObj::json(){
    QString js = fetchFile("30.01.2013.json");
    QString esc_js = escapeJavascriptString(js);
    frame->evaluateJavaScript(QString("sendTestResults('%1')").arg(esc_js));
}


/*=========================================
            Internal function
 ==========================================*/
bool JSBridgeObj::removeDir(QString dirName)
{
    bool result;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

QString JSBridgeObj::escapeJavascriptString(QString str)
{
    QString out;
    QRegExp rx("(\\r|\\n|\\\\|\")");
    int pos = 0, lastPos = 0;

    while ((pos = rx.indexIn(str, pos)) != -1)
    {
        out += str.mid(lastPos, pos - lastPos);

        switch (rx.cap(1).at(0).unicode())
        {
        case '\r':
            out += " ";
            break;
        case '\n':
            out += " ";
            break;
        case '"':
            out += "\\\"";
            break;
        case '\\':
            out += "\\\\";
            break;
        }
        pos++;
        lastPos = pos;
    }
    out += str.mid(lastPos);
    return out;
}
