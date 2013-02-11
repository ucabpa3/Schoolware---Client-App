#include "downloadmanager.h"
#include <QtGui>

DownloadManager::DownloadManager(QObject *parent):
    QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)));
}

void DownloadManager::downloadFile(QString file_url, QString appName, QString appID, QString Cat, QString Desc){
    Category = Cat;
    AppDesc = Desc;
    AppName = appName;
    AppID = appID;
    QUrl url(file_url);
    _manager->get(QNetworkRequest(url));
}

void DownloadManager::downloadFinished(QNetworkReply *reply){

    QUrl url = reply->url();
    if (reply->error())
    {
        uug() << "Download of " <<  url.toEncoded().constData()
                 << " failed: " << reply->errorString();
        downloadCallback("finishedDownload('Download Failed.');");
    }
    else
    {
        QString path = url.path();
        QString temp = QFileInfo(path).fileName();
        if (temp.isEmpty()) temp = "download";

        if(AppDesc == " "){

           // QStringList list = temp.split(".");
            QString filename = AppName+".png";

            QFile file(QDir::currentPath()+"/AppFolder/"+Category+"/"+AppName+"/"+filename);
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(reply->readAll());
                file.close();
            }
            else qDebug() << file.errorString();
        }

        else{

        //QStringList list = fileName.split(".");

        QString MainAppDir = "AppFolder";
        QString initWorkingPath = QDir::currentPath() ;
        if(!QDir(MainAppDir).exists()){
            QDir().mkdir(MainAppDir);
        }

        buildCatHtml();
        QDir::setCurrent(QDir::currentPath() + "/" + MainAppDir); //Appfolder
        if(!QDir(Category).exists()){
            QDir().mkdir(Category);
        }

        QDir::setCurrent(QDir::currentPath() + "/" + Category);//appfolder category
        QString DirName = AppName;

        if(!QDir(DirName).exists()){
            QDir().mkdir(DirName);


        QString completePathToApp = QDir::currentPath() + "/" + DirName +"/"+ temp;
        QFile file(completePathToApp);
        if(!file.exists()){
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(reply->readAll());
                file.close();
                QDir::setCurrent(QDir::currentPath() + "/" + DirName);
                downloadCallback("finishedDownload();");
                QDir::setCurrent(initWorkingPath);
                buildAppHtml(temp, QDir::currentPath() + "/AppFolder/"+ Category + "/" + DirName + "/");
                jsonBuilder(AppName,Category);

            }
            else{
                QDir::setCurrent(initWorkingPath);
                downloadCallback("finishedDownload('Application already exists.');");
            }
        }
        }
        else{
            QDir::setCurrent(initWorkingPath);
            downloadCallback("finishedDownload('Application already exists.');");
        }
        }
    }
}

void DownloadManager::buildAppHtml(QString fileName, QString PathToApp){

    QFile appHtml("appList.html");
    if(!appHtml.exists()){
        if (appHtml.open(QIODevice::WriteOnly)){

            QTextStream stream (&appHtml);

            stream << "<div class=\"installed-app\" category=\""+Category+"\" description=\""+AppDesc+"\">";
            stream << "<a href=\""+PathToApp+fileName+"\"><img src=\""+PathToApp+AppName+".png\"/>"+AppName+"</a>";
            stream << "</div>" << endl;
            appHtml.close();
        }

    }
    else{
        if(appHtml.open(QIODevice::Append)){

            QTextStream stream (&appHtml);
            qDebug() << PathToApp + fileName;
            qDebug() << PathToApp + AppName+".png";
            stream << "<div class=\"installed-app\" category=\""+Category+"\" description=\""+AppDesc+"\">"<<endl;
            stream << "<a href=\""+PathToApp+fileName+"\"><img src=\""+PathToApp+AppName+".png\"/>"+AppName+"</a>";
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

            //stream << "<li class=\"selected\" id=\"all\"><a onfocus=\"blur();\">All</a></li>";
            stream << "<li id=\""+Category+"\"><a onfocus=\"blur();\">"+Category+"</a></li>";

            CatHtml.close();
        }
    }
    else{
        if(CatHtml.open(QIODevice::ReadOnly)){
            QTextStream Rstream(&CatHtml);
            QString read = Rstream.readAll();
            if(!read.contains(Category)){
                CatHtml.close();
                if(CatHtml.open(QIODevice::Append)){
                    QTextStream stream (&CatHtml);
                    stream << "<li id=\""+Category+"\"><a onfocus=\"blur();\">"+Category+"</a></li>"<<endl;
                }
            }
            CatHtml.close();
        }

    }

}

void DownloadManager::jsonBuilder(QString appname, QString category){

    QFile file("update.json");
    if(!file.exists()){
        if (file.open(QIODevice::WriteOnly)){
            QTextStream stream (&file);
            stream << "["<<endl<<"{\"Appname\" : \""+appname+"\",\"AppID\" : \""+AppID+"\",\"Category\":\""+category+"\"}"<<endl<< "]";
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
                        line.append(lineTemp + "\n");

                    }
                    else {

                        line.append(",\n{\"Appname\" : \""+appname+"\",\"AppID\": \""+AppID+"\" ,\"Category\":\""+category+"\"}");
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
