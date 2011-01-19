/****************************************************************************
** Meta object code from reading C++ file 'setuppage.h'
**
** Created: Wed Jan 19 16:16:18 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/setuppage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setuppage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SetupPage[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      46,   10,   10,   10, 0x0a,
      82,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SetupPage[] = {
    "SetupPage\0\0recordOnRadioButtonClickedHandle()\0"
    "recordOffRadioButtonClickedHandle()\0"
    "recordChannelChangedHandle()\0"
};

const QMetaObject SetupPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SetupPage,
      qt_meta_data_SetupPage, 0 }
};

const QMetaObject *SetupPage::metaObject() const
{
    return &staticMetaObject;
}

void *SetupPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetupPage))
        return static_cast<void*>(const_cast< SetupPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int SetupPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: recordOnRadioButtonClickedHandle(); break;
        case 1: recordOffRadioButtonClickedHandle(); break;
        case 2: recordChannelChangedHandle(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
