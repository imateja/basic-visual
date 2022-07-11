/****************************************************************************
** Meta object code from reading C++ file 'ast.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ast/inc/ast.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ast.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExprAST_t {
    const uint offsetsAndSize[28];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ExprAST_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ExprAST_t qt_meta_stringdata_ExprAST = {
    {
QT_MOC_LITERAL(0, 7), // "ExprAST"
QT_MOC_LITERAL(8, 10), // "selectItem"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 8), // "ExprAST*"
QT_MOC_LITERAL(29, 4), // "item"
QT_MOC_LITERAL(34, 15), // "updateSelection"
QT_MOC_LITERAL(50, 17), // "ShouldUpdateScene"
QT_MOC_LITERAL(68, 18), // "updateBoundingRect"
QT_MOC_LITERAL(87, 5), // "Moved"
QT_MOC_LITERAL(93, 14), // "signalSelected"
QT_MOC_LITERAL(108, 19), // "propagateSelectItem"
QT_MOC_LITERAL(128, 24), // "propagateUpdateSelection"
QT_MOC_LITERAL(153, 26), // "propagateShouldUpdateScene"
QT_MOC_LITERAL(180, 27) // "propagateUpdateBoundingRect"

    },
    "ExprAST\0selectItem\0\0ExprAST*\0item\0"
    "updateSelection\0ShouldUpdateScene\0"
    "updateBoundingRect\0Moved\0signalSelected\0"
    "propagateSelectItem\0propagateUpdateSelection\0"
    "propagateShouldUpdateScene\0"
    "propagateUpdateBoundingRect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExprAST[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       5,    0,   77,    2, 0x06,    3 /* Public */,
       6,    0,   78,    2, 0x06,    4 /* Public */,
       7,    0,   79,    2, 0x06,    5 /* Public */,
       8,    0,   80,    2, 0x06,    6 /* Public */,
       9,    0,   81,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   82,    2, 0x0a,    8 /* Public */,
      11,    0,   85,    2, 0x0a,   10 /* Public */,
      12,    0,   86,    2, 0x0a,   11 /* Public */,
      13,    0,   87,    2, 0x0a,   12 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExprAST::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExprAST *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectItem((*reinterpret_cast< ExprAST*(*)>(_a[1]))); break;
        case 1: _t->updateSelection(); break;
        case 2: _t->ShouldUpdateScene(); break;
        case 3: _t->updateBoundingRect(); break;
        case 4: _t->Moved(); break;
        case 5: _t->signalSelected(); break;
        case 6: _t->propagateSelectItem((*reinterpret_cast< ExprAST*(*)>(_a[1]))); break;
        case 7: _t->propagateUpdateSelection(); break;
        case 8: _t->propagateShouldUpdateScene(); break;
        case 9: _t->propagateUpdateBoundingRect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ExprAST* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< ExprAST* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExprAST::*)(ExprAST * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExprAST::selectItem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ExprAST::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExprAST::updateSelection)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ExprAST::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExprAST::ShouldUpdateScene)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ExprAST::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExprAST::updateBoundingRect)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ExprAST::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExprAST::Moved)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ExprAST::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExprAST::signalSelected)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject ExprAST::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsObject::staticMetaObject>(),
    qt_meta_stringdata_ExprAST.offsetsAndSize,
    qt_meta_data_ExprAST,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ExprAST_t
, QtPrivate::TypeAndForceComplete<ExprAST, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ExprAST *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<ExprAST *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ExprAST::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExprAST::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExprAST.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Serializable"))
        return static_cast< Serializable*>(this);
    return QGraphicsObject::qt_metacast(_clname);
}

int ExprAST::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ExprAST::selectItem(ExprAST * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExprAST::updateSelection()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ExprAST::ShouldUpdateScene()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ExprAST::updateBoundingRect()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ExprAST::Moved()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ExprAST::signalSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
