#include "jsbridgeobj.h"
#include <QtGui>

JSBridgeObj::JSBridgeObj(QObject *parent) :
    QObject(parent)
{
}

QString JSBridgeObj::returnStr(){
    return QString("Hello");
}

int JSBridgeObj::returnInt(){
    return 1;
}

void JSBridgeObj::passInt(int i){
    qDebug() << i;
}

int JSBridgeObj::launchJar(QString str){
    qDebug() << str;
    QString cmd = QString("java -jar ").append(str);
    return QProcess::execute(cmd);
   // QProcess::execute( "java", QStringList() << "-jar" << "c:\\myfile.jar" );
}
