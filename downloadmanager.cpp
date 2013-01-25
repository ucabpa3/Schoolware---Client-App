#include "downloadmanager.h"
#include <QtGui>

DownloadManager::DownloadManager(QObject *parent):
    QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::downloadFile(QString file_url, QString Cat){
    Category = Cat;
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

        QStringList list = fileName.split(".");

        QString MainAppDir = "AppFolder";
        QString initWorkingPath = QDir::currentPath() ;
        if(!QDir(MainAppDir).exists()){
            QDir().mkdir(MainAppDir);
        }
        QDir::setCurrent(QDir::currentPath() + "/" + MainAppDir); //Appfolder
        if(!QDir(Category).exists()){
            QDir().mkdir(Category);
            QDir::setCurrent(initWorkingPath);
            buildCatHtml();
            QDir::setCurrent(QDir::currentPath() + "/" + MainAppDir);
        }
        QDir::setCurrent(QDir::currentPath() + "/" + Category);//appfolder category
        qDebug() << list[1];
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
                QDir::setCurrent(QDir::currentPath() + "/" + DirName);
                if(list[1] == "zip"){
                    QString cmd = QString("unzip ").append(fileName);
                    QProcess::execute(cmd);
                }
                downloadCallback("finishedDownload(' ');");
                QDir::setCurrent(initWorkingPath);
                buildAppHtml(fileName, completePathToApp);
                jsonBuilder(fileName,Category);

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

void DownloadManager::buildAppHtml(QString fileName, QString PathToApp){

    //QStringList list = fileName.split(".");
    QFile appHtml("appList.html");
    if(!appHtml.exists()){
        if (appHtml.open(QIODevice::WriteOnly)){

            QTextStream stream (&appHtml);
            stream << "<div class=\"installed-app "+Category+" \">";
            stream << "<a href=\""+PathToApp+"\"><img src=\"img/application_icon.png\"/>"+fileName+"</a>";
            stream << "</div>" << endl;
            appHtml.close();
        }

    }
    else{
        if(appHtml.open(QIODevice::Append)){

            QTextStream stream (&appHtml);
            stream << "<div class=\"installed-app "+Category+"\">"<<endl;
            stream << "<a href=\""+PathToApp+"\"><img src=\"img/application_icon.png\"/>"+fileName+"</a>";
            stream << "</div>" << endl;
            appHtml.close();
        }
    }
}

void DownloadManager::buildCatHtml(){


    QFile CatHtml("cathtml.html");
    if(!CatHtml.exists()){
        if (CatHtml.open(QIODevice::WriteOnly)){
            QTextStream stream (&CatHtml);
            stream << "<li class=\"selected\" id=\"all\"><a onfocus=\"blur();\">All</a></li>";
            stream << "<li id=\""+Category+"\"><a onfocus=\"blur();\">"+Category+"</a></li>";
            CatHtml.close();
        }
    }
    else{
        if(CatHtml.open(QIODevice::Append)){

            QTextStream stream (&CatHtml);
            stream << "<li id=\""+Category+"\"><a onfocus=\"blur();\">"+Category+"</a></li>"<<endl;
            CatHtml.close();
        }

    }

}

void DownloadManager::jsonBuilder(QString appname, QString category){

    QFile file("update.json");
    if(!file.exists()){
        if (file.open(QIODevice::WriteOnly)){
            QTextStream stream (&file);
            stream << "["<<endl<<"{\"Appname\" : \""+appname+"\",\"Category\":\""+category+"\"}"<<endl<< "]";
            file.close();
        }
    }
    else{

            QString line ;
            if(file.open(QIODevice::ReadOnly)){
                QTextStream stream(&file);

                while(!stream.atEnd()){

                    QString lineTemp = stream.readLine();

                    if(lineTemp != "]"){
                        line.append(lineTemp);

                    }
                    else {

                        line.append(",{\"Appname\" : \""+appname+"\",\"Category\":\""+category+"\"}");
                        break;
                    }
                }

                file.close();
                QFile::remove("update.json");
                QFile newFile("update.json");
                if (newFile.open(QIODevice::WriteOnly)){
                    QTextStream stream(&newFile);
                    stream << line << endl << "]";
                    newFile.close();
                }
            }


    }
}
