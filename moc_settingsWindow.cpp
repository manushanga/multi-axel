/****************************************************************************
** Meta object code from reading C++ file 'settingsWindow.h'
**
** Created: Sun May 13 13:59:06 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "settingsWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_settingsWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_settingsWindow[] = {
    "settingsWindow\0\0b\0on_pbBox_clicked(QAbstractButton*)\0"
};

void settingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        settingsWindow *_t = static_cast<settingsWindow *>(_o);
        switch (_id) {
        case 0: _t->on_pbBox_clicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData settingsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject settingsWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_settingsWindow,
      qt_meta_data_settingsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &settingsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *settingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *settingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_settingsWindow))
        return static_cast<void*>(const_cast< settingsWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int settingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
