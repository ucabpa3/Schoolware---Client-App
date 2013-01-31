/****************************************************************************
** Meta object code from reading C++ file 'jsbridgeobj.h'
**
** Created: Thu Jan 31 21:11:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "jsbridgeobj.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jsbridgeobj.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JSBridgeObj[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   17,   13,   12, 0x0a,
      65,   40,   12,   12, 0x0a,
     118,  115,   12,   12, 0x0a,
     148,  139,   12,   12, 0x0a,
     185,  176,  168,   12, 0x0a,
     204,   12,   12,   12, 0x0a,
     237,  220,  211,   12, 0x0a,
     281,  267,   12,   12, 0x0a,
     309,   12,  168,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_JSBridgeObj[] = {
    "JSBridgeObj\0\0int\0str\0launchApp(QString)\0"
    "fileUrl,AppName,Cat,Desc\0"
    "initiateDownload(QString,QString,QString,QString)\0"
    "fr\0setFrame(QWebFrame*)\0callback\0"
    "JSCallback(QString)\0QString\0filename\0"
    "fetchFile(QString)\0json()\0QVariant\0"
    "AppName,Category\0uninstallApp(QString,QString)\0"
    "fileName,data\0updateFile(QString,QString)\0"
    "bootChecks()\0"
};

void JSBridgeObj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        JSBridgeObj *_t = static_cast<JSBridgeObj *>(_o);
        switch (_id) {
        case 0: { int _r = _t->launchApp((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->initiateDownload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->setFrame((*reinterpret_cast< QWebFrame*(*)>(_a[1]))); break;
        case 3: _t->JSCallback((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { QString _r = _t->fetchFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: _t->json(); break;
        case 6: { QVariant _r = _t->uninstallApp((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 7: _t->updateFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: { QString _r = _t->bootChecks();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData JSBridgeObj::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject JSBridgeObj::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JSBridgeObj,
      qt_meta_data_JSBridgeObj, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JSBridgeObj::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JSBridgeObj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JSBridgeObj::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JSBridgeObj))
        return static_cast<void*>(const_cast< JSBridgeObj*>(this));
    return QObject::qt_metacast(_clname);
}

int JSBridgeObj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
