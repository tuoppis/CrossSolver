/****************************************************************************
** Meta object code from reading C++ file 'asyncsolver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../asyncsolver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'asyncsolver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AsyncSolver_t {
    const uint offsetsAndSize[86];
    char stringdata0[452];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_AsyncSolver_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_AsyncSolver_t qt_meta_stringdata_AsyncSolver = {
    {
QT_MOC_LITERAL(0, 11), // "AsyncSolver"
QT_MOC_LITERAL(12, 12), // "resultsReady"
QT_MOC_LITERAL(25, 0), // ""
QT_MOC_LITERAL(26, 12), // "hasSolutions"
QT_MOC_LITERAL(39, 15), // "progressChanged"
QT_MOC_LITERAL(55, 7), // "percent"
QT_MOC_LITERAL(63, 16), // "solutionsChanged"
QT_MOC_LITERAL(80, 4), // "sols"
QT_MOC_LITERAL(85, 9), // "beginWork"
QT_MOC_LITERAL(95, 6), // "needed"
QT_MOC_LITERAL(102, 17), // "dictionaryChanged"
QT_MOC_LITERAL(120, 3), // "url"
QT_MOC_LITERAL(124, 8), // "canceled"
QT_MOC_LITERAL(133, 17), // "hasPartialResults"
QT_MOC_LITERAL(151, 16), // "isWorkingChanged"
QT_MOC_LITERAL(168, 3), // "val"
QT_MOC_LITERAL(172, 16), // "resultsInChanged"
QT_MOC_LITERAL(189, 19), // "extendedInfoChanged"
QT_MOC_LITERAL(209, 6), // "status"
QT_MOC_LITERAL(216, 10), // "beginAsync"
QT_MOC_LITERAL(227, 8), // "exsolver"
QT_MOC_LITERAL(236, 6), // "solver"
QT_MOC_LITERAL(243, 12), // "needed_words"
QT_MOC_LITERAL(256, 5), // "width"
QT_MOC_LITERAL(262, 6), // "height"
QT_MOC_LITERAL(269, 5), // "words"
QT_MOC_LITERAL(275, 10), // "cancelWork"
QT_MOC_LITERAL(286, 14), // "receiveProgess"
QT_MOC_LITERAL(301, 2), // "id"
QT_MOC_LITERAL(304, 17), // "receiveCompletion"
QT_MOC_LITERAL(322, 6), // "rowsAt"
QT_MOC_LITERAL(329, 3), // "idx"
QT_MOC_LITERAL(333, 9), // "columnsAt"
QT_MOC_LITERAL(343, 7), // "comboAt"
QT_MOC_LITERAL(351, 13), // "saveResultsTo"
QT_MOC_LITERAL(365, 7), // "heading"
QT_MOC_LITERAL(373, 15), // "dictionaryWords"
QT_MOC_LITERAL(389, 8), // "progress"
QT_MOC_LITERAL(398, 9), // "solutions"
QT_MOC_LITERAL(408, 10), // "dictionary"
QT_MOC_LITERAL(419, 9), // "resultsIn"
QT_MOC_LITERAL(429, 9), // "isWorking"
QT_MOC_LITERAL(439, 12) // "extendedInfo"

    },
    "AsyncSolver\0resultsReady\0\0hasSolutions\0"
    "progressChanged\0percent\0solutionsChanged\0"
    "sols\0beginWork\0needed\0dictionaryChanged\0"
    "url\0canceled\0hasPartialResults\0"
    "isWorkingChanged\0val\0resultsInChanged\0"
    "extendedInfoChanged\0status\0beginAsync\0"
    "exsolver\0solver\0needed_words\0width\0"
    "height\0words\0cancelWork\0receiveProgess\0"
    "id\0receiveCompletion\0rowsAt\0idx\0"
    "columnsAt\0comboAt\0saveResultsTo\0heading\0"
    "dictionaryWords\0progress\0solutions\0"
    "dictionary\0resultsIn\0isWorking\0"
    "extendedInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AsyncSolver[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       6,  200, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  134,    2, 0x06,    7 /* Public */,
       4,    1,  137,    2, 0x06,    9 /* Public */,
       6,    1,  140,    2, 0x06,   11 /* Public */,
       8,    1,  143,    2, 0x06,   13 /* Public */,
      10,    1,  146,    2, 0x06,   15 /* Public */,
      12,    1,  149,    2, 0x06,   17 /* Public */,
      14,    1,  152,    2, 0x06,   19 /* Public */,
      16,    1,  155,    2, 0x06,   21 /* Public */,
      17,    1,  158,    2, 0x06,   23 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      19,    2,  161,    2, 0x0a,   25 /* Public */,
      19,    3,  166,    2, 0x0a,   28 /* Public */,
      26,    0,  173,    2, 0x0a,   32 /* Public */,
      27,    2,  174,    2, 0x09,   33 /* Protected */,
      29,    1,  179,    2, 0x09,   36 /* Protected */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      30,    1,  182,    2, 0x102,   38 /* Public | MethodIsConst  */,
      32,    1,  185,    2, 0x102,   40 /* Public | MethodIsConst  */,
      33,    1,  188,    2, 0x102,   42 /* Public | MethodIsConst  */,
      34,    2,  191,    2, 0x102,   44 /* Public | MethodIsConst  */,
      34,    1,  196,    2, 0x122,   47 /* Public | MethodCloned | MethodIsConst  */,
      36,    0,  199,    2, 0x102,   49 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QStringList,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Bool,   18,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20, QMetaType::QStringList,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   23,   24,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,    5,
    QMetaType::Void, QMetaType::Int,   28,

 // methods: parameters
    QMetaType::QString, QMetaType::Int,   31,
    QMetaType::QString, QMetaType::Int,   31,
    QMetaType::QString, QMetaType::Int,   31,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   11,   35,
    QMetaType::Bool, QMetaType::QString,   11,
    QMetaType::Int,

 // properties: name, type, flags
      37, QMetaType::Int, 0x00015103, uint(1), 0,
      38, QMetaType::Int, 0x00015001, uint(2), 0,
      39, QMetaType::QString, 0x00015103, uint(4), 0,
      40, QMetaType::QString, 0x00015103, uint(7), 0,
      41, QMetaType::Bool, 0x00015001, uint(6), 0,
      42, QMetaType::Bool, 0x00015103, uint(8), 0,

       0        // eod
};

void AsyncSolver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AsyncSolver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->resultsReady((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->progressChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->solutionsChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->beginWork((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 4: _t->dictionaryChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->canceled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->isWorkingChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->resultsInChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->extendedInfoChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->beginAsync((*reinterpret_cast< std::add_pointer_t<exsolver>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 10: _t->beginAsync((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 11: _t->cancelWork(); break;
        case 12: _t->receiveProgess((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 13: _t->receiveCompletion((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: { QString _r = _t->rowsAt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 15: { QString _r = _t->columnsAt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 16: { QString _r = _t->comboAt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 17: { bool _r = _t->saveResultsTo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: { bool _r = _t->saveResultsTo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { int _r = _t->dictionaryWords();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AsyncSolver::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::resultsReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::progressChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::solutionsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::beginWork)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::dictionaryChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::canceled)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::isWorkingChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::resultsInChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AsyncSolver::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsyncSolver::extendedInfoChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AsyncSolver *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->progress(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->solutions(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->dictionary(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->resultsIn(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->isWorking(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->extendedInfo(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AsyncSolver *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setProgress(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setDictionary(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setResultsIn(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setExtendedInfo(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject AsyncSolver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AsyncSolver.offsetsAndSize,
    qt_meta_data_AsyncSolver,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AsyncSolver_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<AsyncSolver, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const exsolver &, std::false_type>, QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *AsyncSolver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AsyncSolver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AsyncSolver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AsyncSolver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AsyncSolver::resultsReady(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AsyncSolver::progressChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AsyncSolver::solutionsChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AsyncSolver::beginWork(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AsyncSolver::dictionaryChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AsyncSolver::canceled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AsyncSolver::isWorkingChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AsyncSolver::resultsInChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AsyncSolver::extendedInfoChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
