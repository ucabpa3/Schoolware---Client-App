#ifndef JSBRIDGEOBJ_H
#define JSBRIDGEOBJ_H

#include <QObject>
#include <QWebFrame>
#include "downloadmanager.h"

class JSBridgeObj : public QObject
{
    Q_OBJECT
public:
    explicit JSBridgeObj(QObject *parent = 0);

signals:

public slots:
    int launchApp(QString str);
    void initiateDownload(QString fileUrl,QString AppName,QString appID, QString Cat, QString Desc);
    void setFrame(QWebFrame *fr);
    void JSCallback(QString callback);
    QString fetchFile(QString filename);
    void json();
    QVariant uninstallApp(QString AppName, QString Category);
    void updateFile(QString fileName, QString data);
    QString bootChecks();

private:
    QWebFrame *frame;
    QString escapeJavascriptString(QString str);
    bool removeDir(QString dirName);
    bool dependancyCheck(QString dep);
};

#endif // JSBRIDGEOBJ_H
