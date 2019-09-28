/****************************************************************************
** Meta object code from reading C++ file 'passengerflowcount.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../passengerflowcount.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'passengerflowcount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PassengerFlowCount_t {
    QByteArrayData data[10];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PassengerFlowCount_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PassengerFlowCount_t qt_meta_stringdata_PassengerFlowCount = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PassengerFlowCount"
QT_MOC_LITERAL(1, 19, 11), // "dataChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "initEnvironment"
QT_MOC_LITERAL(4, 48, 19), // "selectPassengerFlow"
QT_MOC_LITERAL(5, 68, 6), // "sexMap"
QT_MOC_LITERAL(6, 75, 6), // "ageMap"
QT_MOC_LITERAL(7, 82, 6), // "maleCt"
QT_MOC_LITERAL(8, 89, 8), // "femaleCt"
QT_MOC_LITERAL(9, 98, 11) // "ageCountMap"

    },
    "PassengerFlowCount\0dataChanged\0\0"
    "initEnvironment\0selectPassengerFlow\0"
    "sexMap\0ageMap\0maleCt\0femaleCt\0ageCountMap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PassengerFlowCount[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       5,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,

 // properties: name, type, flags
       5, QMetaType::QVariantMap, 0x00095401,
       6, QMetaType::QVariantMap, 0x00095401,
       7, QMetaType::Int, 0x00095401,
       8, QMetaType::Int, 0x00095401,
       9, QMetaType::QVariant, 0x00095401,

       0        // eod
};

void PassengerFlowCount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PassengerFlowCount *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: { bool _r = _t->initEnvironment();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->selectPassengerFlow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PassengerFlowCount::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PassengerFlowCount::dataChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PassengerFlowCount *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantMap*>(_v) = _t->m_sexMap; break;
        case 1: *reinterpret_cast< QVariantMap*>(_v) = _t->m_ageMap; break;
        case 2: *reinterpret_cast< int*>(_v) = _t->m_maleCt; break;
        case 3: *reinterpret_cast< int*>(_v) = _t->m_femaleCt; break;
        case 4: *reinterpret_cast< QVariant*>(_v) = _t->m_ageCountMap; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PassengerFlowCount::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_PassengerFlowCount.data,
    qt_meta_data_PassengerFlowCount,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PassengerFlowCount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PassengerFlowCount::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PassengerFlowCount.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PassengerFlowCount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PassengerFlowCount::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
