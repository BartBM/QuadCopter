/****************************************************************************
** Meta object code from reading C++ file 'minmaxaxisvalues.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../quadcopter/imu-calibrate/minmaxaxisvalues.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'minmaxaxisvalues.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MinMaxAxisValues_t {
    QByteArrayData data[11];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MinMaxAxisValues_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MinMaxAxisValues_t qt_meta_stringdata_MinMaxAxisValues = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MinMaxAxisValues"
QT_MOC_LITERAL(1, 17, 7), // "getMinX"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "getX"
QT_MOC_LITERAL(4, 31, 7), // "getMaxX"
QT_MOC_LITERAL(5, 39, 7), // "getMinY"
QT_MOC_LITERAL(6, 47, 4), // "getY"
QT_MOC_LITERAL(7, 52, 7), // "getMaxY"
QT_MOC_LITERAL(8, 60, 7), // "getMinZ"
QT_MOC_LITERAL(9, 68, 4), // "getZ"
QT_MOC_LITERAL(10, 73, 7) // "getMaxZ"

    },
    "MinMaxAxisValues\0getMinX\0\0getX\0getMaxX\0"
    "getMinY\0getY\0getMaxY\0getMinZ\0getZ\0"
    "getMaxZ"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MinMaxAxisValues[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,

       0        // eod
};

void MinMaxAxisValues::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MinMaxAxisValues *_t = static_cast<MinMaxAxisValues *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { float _r = _t->getMinX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 1: { float _r = _t->getX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 2: { float _r = _t->getMaxX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 3: { float _r = _t->getMinY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 4: { float _r = _t->getY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 5: { float _r = _t->getMaxY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 6: { float _r = _t->getMinZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 7: { float _r = _t->getZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 8: { float _r = _t->getMaxZ();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MinMaxAxisValues::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MinMaxAxisValues.data,
      qt_meta_data_MinMaxAxisValues,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MinMaxAxisValues::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinMaxAxisValues::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MinMaxAxisValues.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MinMaxAxisValues::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
