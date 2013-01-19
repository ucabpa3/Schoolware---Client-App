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

void JSBridgeObj::initiateDownload(QString fileUrl){
    DownloadManager *manager = new DownloadManager();
    manager->downloadFile(fileUrl);
    connect(manager,SIGNAL(downloadCallback(QString)),SLOT(JSCallback(QString)));
}

/*Callback*/

void JSBridgeObj::JSCallback(QString callback){
    frame->evaluateJavaScript(callback);
}
