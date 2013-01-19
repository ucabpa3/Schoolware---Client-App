#include "downloadmanager.h"
#include <QtGui>

DownloadManager::DownloadManager(QObject *parent):
    QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::downloadFile(QString file_url){
    QUrl url(file_url);
    _manager->get(QNetworkRequest(url));
}

void DownloadManager::downloadFinished(QNetworkReply *reply){

    QUrl url = reply->url();
       if (reply->error())
       {
           qDebug() << "Download of " <<  url.toEncoded().constData()
                    << " failed: " << reply->errorString();
           downloadCallback("finishedDownload('Download Failed.');");
       }
       else
       {
           QString path = url.path();
           QString fileName = QFileInfo(path).fileName();
           if (fileName.isEmpty()) fileName = "download";

           QString DirName = fileName + " App";

           if(!QDir(DirName).exists()){
               QDir().mkdir(DirName);
           }
           else qDebug()<<"Dir exists";

           QFile file(QDir::currentPath() + "/" + DirName +"/"+ fileName);
           if(!file.exists()){
            if (file.open(QIODevice::WriteOnly))
            {
                 file.write(reply->readAll());
                 file.close();
                 downloadCallback("finishedDownload('Download Complete.');");
            }
            else{
                downloadCallback("finishedDownload('Application already exists.');");
             }
           }
           else{
               downloadCallback("finishedDownload('Application already exists.');");
            }
       }
}
