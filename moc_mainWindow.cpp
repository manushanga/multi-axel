/****************************************************************************
** Meta object code from reading C++ file 'mainWindow.h'
**
** Created: Sun May 13 21:42:20 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      46,   11,   11,   11, 0x0a,
      73,   11,   11,   11, 0x0a,
     103,   11,   11,   11, 0x0a,
     122,   11,   11,   11, 0x0a,
     143,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainWindow[] = {
    "mainWindow\0\0on_actionNew_Download_triggered()\0"
    "on_actionAbout_triggered()\0"
    "on_actionSettings_triggered()\0"
    "on_pbAdd_clicked()\0on_pbStart_clicked()\0"
    "on_pbStop_clicked()\0"
};

void mainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainWindow *_t = static_cast<mainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_actionNew_Download_triggered(); break;
        case 1: _t->on_actionAbout_triggered(); break;
        case 2: _t->on_actionSettings_triggered(); break;
        case 3: _t->on_pbAdd_clicked(); break;
        case 4: _t->on_pbStart_clicked(); break;
        case 5: _t->on_pbStop_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData mainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainWindow,
      qt_meta_data_mainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainWindow))
        return static_cast<void*>(const_cast< mainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
