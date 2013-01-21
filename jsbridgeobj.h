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
    int launchJar(QString str);
    void initiateDownload(QString fileUrl);
    QString fetchAppHtml();
    void setFrame(QWebFrame *fr);
    void JSCallback(QString callback);

private:
    QWebFrame *frame;
};

#endif // JSBRIDGEOBJ_H
