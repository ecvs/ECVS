/****************************************************************************
** Meta object code from reading C++ file 'BilateralFilterSet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BilateralFilterSet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BilateralFilterSet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CBilateralFilterSet_t {
    QByteArrayData data[13];
    char stringdata[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CBilateralFilterSet_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CBilateralFilterSet_t qt_meta_stringdata_CBilateralFilterSet = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CBilateralFilterSet"
QT_MOC_LITERAL(1, 20, 9), // "OnOpenImg"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "OnShowFixSize"
QT_MOC_LITERAL(4, 45, 16), // "OnSliderDChanged"
QT_MOC_LITERAL(5, 62, 6), // "nValue"
QT_MOC_LITERAL(6, 69, 25), // "OnSliderSigmaColorChanged"
QT_MOC_LITERAL(7, 95, 25), // "OnSliderSigmaSpaceChanged"
QT_MOC_LITERAL(8, 121, 14), // "OnSpinDChanged"
QT_MOC_LITERAL(9, 136, 23), // "OnSpinSigmaColorChanged"
QT_MOC_LITERAL(10, 160, 23), // "OnSpinSigmaSpaceChanged"
QT_MOC_LITERAL(11, 184, 11), // "OnOkClicked"
QT_MOC_LITERAL(12, 196, 15) // "OnCancelClicled"

    },
    "CBilateralFilterSet\0OnOpenImg\0\0"
    "OnShowFixSize\0OnSliderDChanged\0nValue\0"
    "OnSliderSigmaColorChanged\0"
    "OnSliderSigmaSpaceChanged\0OnSpinDChanged\0"
    "OnSpinSigmaColorChanged\0OnSpinSigmaSpaceChanged\0"
    "OnOkClicked\0OnCancelClicled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CBilateralFilterSet[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    1,   66,    2, 0x08 /* Private */,
       6,    1,   69,    2, 0x08 /* Private */,
       7,    1,   72,    2, 0x08 /* Private */,
       8,    1,   75,    2, 0x08 /* Private */,
       9,    1,   78,    2, 0x08 /* Private */,
      10,    1,   81,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CBilateralFilterSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CBilateralFilterSet *_t = static_cast<CBilateralFilterSet *>(_o);
        switch (_id) {
        case 0: _t->OnOpenImg(); break;
        case 1: _t->OnShowFixSize(); break;
        case 2: _t->OnSliderDChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnSliderSigmaColorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->OnSliderSigmaSpaceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->OnSpinDChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->OnSpinSigmaColorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->OnSpinSigmaSpaceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->OnOkClicked(); break;
        case 9: _t->OnCancelClicled(); break;
        default: ;
        }
    }
}

const QMetaObject CBilateralFilterSet::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CBilateralFilterSet.data,
      qt_meta_data_CBilateralFilterSet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CBilateralFilterSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CBilateralFilterSet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CBilateralFilterSet.stringdata))
        return static_cast<void*>(const_cast< CBilateralFilterSet*>(this));
    return QDialog::qt_metacast(_clname);
}

int CBilateralFilterSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
