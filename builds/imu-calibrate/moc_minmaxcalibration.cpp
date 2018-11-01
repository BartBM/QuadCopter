/****************************************************************************
** Meta object code from reading C++ file 'minmaxcalibration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../quadcopter/imu-calibrate/minmaxcalibration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'minmaxcalibration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MinMaxCalibration_t {
    QByteArrayData data[5];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MinMaxCalibration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MinMaxCalibration_t qt_meta_stringdata_MinMaxCalibration = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MinMaxCalibration"
QT_MOC_LITERAL(1, 18, 23), // "minMaxAxisValuesChanged"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 19), // "getMinMaxAxisValues"
QT_MOC_LITERAL(4, 63, 17) // "MinMaxAxisValues*"

    },
    "MinMaxCalibration\0minMaxAxisValuesChanged\0"
    "\0getMinMaxAxisValues\0MinMaxAxisValues*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MinMaxCalibration[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    0x80000000 | 4,

       0        // eod
};

void MinMaxCalibration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MinMaxCalibration *_t = static_cast<MinMaxCalibration *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->minMaxAxisValuesChanged(); break;
        case 1: { MinMaxAxisValues* _r = _t->getMinMaxAxisValues();
            if (_a[0]) *reinterpret_cast< MinMaxAxisValues**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MinMaxCalibration::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinMaxCalibration::minMaxAxisValuesChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MinMaxCalibration::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MinMaxCalibration.data,
      qt_meta_data_MinMaxCalibration,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MinMaxCalibration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinMaxCalibration::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MinMaxCalibration.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MinMaxCalibration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void MinMaxCalibration::minMaxAxisValuesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
