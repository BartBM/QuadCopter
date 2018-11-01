/****************************************************************************
** Meta object code from reading C++ file 'minmaxdataseries.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../quadcopter/imu-calibrate/minmaxdataseries.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'minmaxdataseries.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MinMaxDataSeries_t {
    QByteArrayData data[9];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MinMaxDataSeries_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MinMaxDataSeries_t qt_meta_stringdata_MinMaxDataSeries = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MinMaxDataSeries"
QT_MOC_LITERAL(1, 17, 22), // "updateMinMaxDataSeries"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 23), // "processMinMaxAxisValues"
QT_MOC_LITERAL(4, 65, 17), // "MinMaxAxisValues*"
QT_MOC_LITERAL(5, 83, 6), // "values"
QT_MOC_LITERAL(6, 90, 19), // "getMinMaxDataSeries"
QT_MOC_LITERAL(7, 110, 12), // "QLineSeries*"
QT_MOC_LITERAL(8, 123, 11) // "xLineSeries"

    },
    "MinMaxDataSeries\0updateMinMaxDataSeries\0"
    "\0processMinMaxAxisValues\0MinMaxAxisValues*\0"
    "values\0getMinMaxDataSeries\0QLineSeries*\0"
    "xLineSeries"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MinMaxDataSeries[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       1,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x0a /* Public */,
       6,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    0x80000000 | 7,

 // properties: name, type, flags
       8, 0x80000000 | 7, 0x00495009,

 // properties: notify_signal_id
       0,

       0        // eod
};

void MinMaxDataSeries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MinMaxDataSeries *_t = static_cast<MinMaxDataSeries *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateMinMaxDataSeries(); break;
        case 1: _t->processMinMaxAxisValues((*reinterpret_cast< MinMaxAxisValues*(*)>(_a[1]))); break;
        case 2: { QLineSeries* _r = _t->getMinMaxDataSeries();
            if (_a[0]) *reinterpret_cast< QLineSeries**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MinMaxAxisValues* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MinMaxDataSeries::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinMaxDataSeries::updateMinMaxDataSeries)) {
                *result = 0;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLineSeries* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        MinMaxDataSeries *_t = static_cast<MinMaxDataSeries *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QLineSeries**>(_v) = _t->getMinMaxDataSeries(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject MinMaxDataSeries::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MinMaxDataSeries.data,
      qt_meta_data_MinMaxDataSeries,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MinMaxDataSeries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinMaxDataSeries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MinMaxDataSeries.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MinMaxDataSeries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MinMaxDataSeries::updateMinMaxDataSeries()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
