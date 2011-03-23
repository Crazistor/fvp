/****************************************************************************
** Meta object code from reading C++ file 'searchdevicepage.h'
**
** Created: Wed Mar 23 18:04:45 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../searchdevicepage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchdevicepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SearchDevicePage[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SearchDevicePage[] = {
    "SearchDevicePage\0\0searchDeviceHandle()\0"
};

const QMetaObject SearchDevicePage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SearchDevicePage,
      qt_meta_data_SearchDevicePage, 0 }
};

const QMetaObject *SearchDevicePage::metaObject() const
{
    return &staticMetaObject;
}

void *SearchDevicePage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SearchDevicePage))
        return static_cast<void*>(const_cast< SearchDevicePage*>(this));
    return QWidget::qt_metacast(_clname);
}

int SearchDevicePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: searchDeviceHandle(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
