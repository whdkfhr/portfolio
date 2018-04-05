/****************************************************************************
** Meta object code from reading C++ file 'Player.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Player_t {
    QByteArrayData data[23];
    char stringdata0[360];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Player_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Player_t qt_meta_stringdata_Player = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Player"
QT_MOC_LITERAL(1, 7, 12), // "set1stWidget"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 5), // "image"
QT_MOC_LITERAL(4, 27, 12), // "set2ndWidget"
QT_MOC_LITERAL(5, 40, 12), // "set3rdWidget"
QT_MOC_LITERAL(6, 53, 25), // "setForwardHeadProgressBar"
QT_MOC_LITERAL(7, 79, 25), // "setTwistedBackProgressBar"
QT_MOC_LITERAL(8, 105, 18), // "setHandOnFaceCount"
QT_MOC_LITERAL(9, 124, 32), // "update_forward_head_chart_signal"
QT_MOC_LITERAL(10, 157, 4), // "time"
QT_MOC_LITERAL(11, 162, 5), // "grade"
QT_MOC_LITERAL(12, 168, 33), // "update_slant_posture_chart_si..."
QT_MOC_LITERAL(13, 202, 5), // "value"
QT_MOC_LITERAL(14, 208, 32), // "update_hand_on_face_chart_signal"
QT_MOC_LITERAL(15, 241, 11), // "is_detected"
QT_MOC_LITERAL(16, 253, 24), // "whether_to_scroll_signal"
QT_MOC_LITERAL(17, 278, 16), // "handOnFaceSignal"
QT_MOC_LITERAL(18, 295, 16), // "turtleNeckSignal"
QT_MOC_LITERAL(19, 312, 17), // "twistedBackSignal"
QT_MOC_LITERAL(20, 330, 11), // "player_echo"
QT_MOC_LITERAL(21, 342, 7), // "message"
QT_MOC_LITERAL(22, 350, 9) // "onTimeout"

    },
    "Player\0set1stWidget\0\0image\0set2ndWidget\0"
    "set3rdWidget\0setForwardHeadProgressBar\0"
    "setTwistedBackProgressBar\0setHandOnFaceCount\0"
    "update_forward_head_chart_signal\0time\0"
    "grade\0update_slant_posture_chart_signal\0"
    "value\0update_hand_on_face_chart_signal\0"
    "is_detected\0whether_to_scroll_signal\0"
    "handOnFaceSignal\0turtleNeckSignal\0"
    "twistedBackSignal\0player_echo\0message\0"
    "onTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Player[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,
       5,    1,   95,    2, 0x06 /* Public */,
       6,    1,   98,    2, 0x06 /* Public */,
       7,    1,  101,    2, 0x06 /* Public */,
       8,    1,  104,    2, 0x06 /* Public */,
       9,    2,  107,    2, 0x06 /* Public */,
      12,    2,  112,    2, 0x06 /* Public */,
      14,    2,  117,    2, 0x06 /* Public */,
      16,    1,  122,    2, 0x06 /* Public */,
      17,    0,  125,    2, 0x06 /* Public */,
      18,    0,  126,    2, 0x06 /* Public */,
      19,    0,  127,    2, 0x06 /* Public */,
      20,    1,  128,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    0,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QReal, QMetaType::Short,   10,   11,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   10,   13,
    QMetaType::Void, QMetaType::QReal, QMetaType::Bool,   10,   15,
    QMetaType::Void, QMetaType::QReal,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Player *_t = static_cast<Player *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set1stWidget((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->set2ndWidget((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->set3rdWidget((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 3: _t->setForwardHeadProgressBar((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 4: _t->setTwistedBackProgressBar((*reinterpret_cast< const qreal(*)>(_a[1]))); break;
        case 5: _t->setHandOnFaceCount((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->update_forward_head_chart_signal((*reinterpret_cast< const qreal(*)>(_a[1])),(*reinterpret_cast< const qint16(*)>(_a[2]))); break;
        case 7: _t->update_slant_posture_chart_signal((*reinterpret_cast< const qreal(*)>(_a[1])),(*reinterpret_cast< const qreal(*)>(_a[2]))); break;
        case 8: _t->update_hand_on_face_chart_signal((*reinterpret_cast< const qreal(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2]))); break;
        case 9: _t->whether_to_scroll_signal((*reinterpret_cast< const qreal(*)>(_a[1]))); break;
        case 10: _t->handOnFaceSignal(); break;
        case 11: _t->turtleNeckSignal(); break;
        case 12: _t->twistedBackSignal(); break;
        case 13: _t->player_echo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Player::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::set1stWidget)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::set2ndWidget)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const QImage & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::set3rdWidget)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::setForwardHeadProgressBar)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::setTwistedBackProgressBar)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::setHandOnFaceCount)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const qreal , const qint16 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::update_forward_head_chart_signal)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const qreal , const qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::update_slant_posture_chart_signal)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const qreal , const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::update_hand_on_face_chart_signal)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const qreal );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::whether_to_scroll_signal)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (Player::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::handOnFaceSignal)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (Player::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::turtleNeckSignal)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (Player::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::twistedBackSignal)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::player_echo)) {
                *result = 13;
                return;
            }
        }
    }
}

const QMetaObject Player::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Player.data,
      qt_meta_data_Player,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Player.stringdata0))
        return static_cast<void*>(const_cast< Player*>(this));
    return QThread::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Player::set1stWidget(const QImage & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Player::set2ndWidget(const QImage & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Player::set3rdWidget(const QImage & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Player::setForwardHeadProgressBar(const int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Player::setTwistedBackProgressBar(const qreal _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Player::setHandOnFaceCount(const int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Player::update_forward_head_chart_signal(const qreal _t1, const qint16 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Player::update_slant_posture_chart_signal(const qreal _t1, const qreal _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Player::update_hand_on_face_chart_signal(const qreal _t1, const bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Player::whether_to_scroll_signal(const qreal _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Player::handOnFaceSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void Player::turtleNeckSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void Player::twistedBackSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void Player::player_echo(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_END_MOC_NAMESPACE
