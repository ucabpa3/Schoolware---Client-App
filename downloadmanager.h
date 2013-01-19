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
    void downloadFile(QString file_url);

signals:
    void downloadCallback(QString callback);
    void failedDown();

private:
    QNetworkAccessManager* _manager;

private slots:
    void downloadFinished(QNetworkReply *reply);

};

#endif // DOWNLOADMANAGER_H
