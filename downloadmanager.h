#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QWebView>

class DownloadManager: public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);

public slots:
    void downloadFile(QString file_url, QString Cat, QString Desc);

signals:
    void downloadCallback(QString callback);
    void failedDown();

private:
    QNetworkAccessManager* _manager;
    QString Category;
    QString AppDesc;

private slots:
    void downloadFinished(QNetworkReply *reply);
    void buildAppHtml(QString fileName,  QString PathToApp);
    void buildCatHtml();
    void jsonBuilder(QString appname, QString category);

};

#endif // DOWNLOADMANAGER_H
