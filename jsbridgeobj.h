#ifndef JSBRIDGEOBJ_H
#define JSBRIDGEOBJ_H

#include <QObject>

class JSBridgeObj : public QObject
{
    Q_OBJECT
public:
    explicit JSBridgeObj(QObject *parent = 0);

signals:

public slots:
    QString returnStr();
    int returnInt();
    void passInt(int i);
    int launchJar(QString str);
};

#endif // JSBRIDGEOBJ_H
