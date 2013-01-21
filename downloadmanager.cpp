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

           QString MainAppDir = "AppFolder";
           QString prevWorkingPath = QDir::currentPath() ;
           if(!QDir(MainAppDir).exists()){
               QDir().mkdir(MainAppDir);
           }
           QDir::setCurrent(QDir::currentPath() + "/" + MainAppDir + "/");

           QString DirName = fileName + "App";

           if(!QDir(DirName).exists()){
               QDir().mkdir(DirName);
           }
           QString completePathToApp = QDir::currentPath() + "/" + DirName +"/"+ fileName;
           QFile file(completePathToApp);
           if(!file.exists()){
            if (file.open(QIODevice::WriteOnly))
            {
                 file.write(reply->readAll());
                 file.close();
                 downloadCallback("finishedDownload('Download Complete.');");
                 buildAppHtml(fileName, completePathToApp);

            }
            else{
                downloadCallback("finishedDownload('Application already exists.');");
             }
           }
           else{
               downloadCallback("finishedDownload('Application already exists.');");
            }
           QDir::setCurrent(prevWorkingPath);
       }
}

void DownloadManager::buildAppHtml(QString fileName, QString PathToApp){

    QStringList list = fileName.split(".");
    QFile appHtml("appList.Html");
    if(!appHtml.exists()){
           if (appHtml.open(QIODevice::WriteOnly)){

               QTextStream stream (&appHtml);
               stream << "<div class=\"installed-app\">"<<endl;
               stream << "<a href=\""+PathToApp+"\"><img src=\"img/application_icon.png\"/>"+list[0]+"</a>"<<endl;
               stream << "</div>" << endl;
               appHtml.close();
           }

     }
    else{
              if(appHtml.open(QIODevice::Append)){

                  QTextStream stream (&appHtml);
                  stream << "<div class=\"installed-app\">"<<endl;
                  stream << "<a href=\""+PathToApp+"\"><img src=\"img/application_icon.png\"/>"+list[0]+"</a>"<<endl;
                  stream << "</div>" << endl;
                  appHtml.close();
              }
    }
}

void DownloadManager::buildCatHtml(QString fileName, QString PathToApp){

}
