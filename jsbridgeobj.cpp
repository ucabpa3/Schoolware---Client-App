#include "jsbridgeobj.h"
#include <QtGui>

JSBridgeObj::JSBridgeObj(QObject *parent) :
    QObject(parent)
{
}

void JSBridgeObj::setFrame(QWebFrame *fr){
    frame = fr;
}

/*Calls from JavaScript*/

int JSBridgeObj::launchJar(QString str){

    QString cmd = QString("java -jar ").append(str);
    return QProcess::execute(cmd);
   // QProcess::execute( "java", QStringList() << "-jar" << "c:\\myfile.jar" );
}

void JSBridgeObj::initiateDownload(QString fileUrl,QString Cat){
    DownloadManager *manager = new DownloadManager();
    manager->downloadFile(fileUrl, Cat);
    connect(manager,SIGNAL(downloadCallback(QString)),SLOT(JSCallback(QString)));
}

/*Callback*/

void JSBridgeObj::JSCallback(QString callback){
    frame->evaluateJavaScript(callback);
}

QVariant JSBridgeObj::appExists(QString AppName){
    QFile file("appList.html");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);

        while(!stream.atEnd()){
            QString line = stream.readLine();
            if(line.contains(AppName)){
                file.close();
                return true;
            }
        }
    }
    return false;
}


QString JSBridgeObj::fetchFile(QString filename){

    QFile file (filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            return stream.readAll();
        }
    file.close();
    return " ";
}
