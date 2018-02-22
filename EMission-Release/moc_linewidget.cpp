/****************************************************************************
** Meta object code from reading C++ file 'linewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EMissionGUI/linewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'linewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lineWidget_t {
    QByteArrayData data[16];
    char stringdata0[305];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lineWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lineWidget_t qt_meta_stringdata_lineWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "lineWidget"
QT_MOC_LITERAL(1, 11, 18), // "on_btnLine_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 18), // "on_btnRect_clicked"
QT_MOC_LITERAL(4, 50, 21), // "on_btnEllipse_clicked"
QT_MOC_LITERAL(5, 72, 22), // "on_btnArcStart_clicked"
QT_MOC_LITERAL(6, 95, 21), // "on_btnArcSpan_clicked"
QT_MOC_LITERAL(7, 117, 17), // "on_btnArc_clicked"
QT_MOC_LITERAL(8, 135, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(9, 154, 19), // "on_btnClear_clicked"
QT_MOC_LITERAL(10, 174, 20), // "on_btnUpload_clicked"
QT_MOC_LITERAL(11, 195, 17), // "on_btnRun_clicked"
QT_MOC_LITERAL(12, 213, 21), // "on_btnVoltage_clicked"
QT_MOC_LITERAL(13, 235, 24), // "on_btnMaxVoltage_clicked"
QT_MOC_LITERAL(14, 260, 20), // "on_btnErrtol_clicked"
QT_MOC_LITERAL(15, 281, 23) // "on_btnLineWidth_clicked"

    },
    "lineWidget\0on_btnLine_clicked\0\0"
    "on_btnRect_clicked\0on_btnEllipse_clicked\0"
    "on_btnArcStart_clicked\0on_btnArcSpan_clicked\0"
    "on_btnArc_clicked\0on_btnSave_clicked\0"
    "on_btnClear_clicked\0on_btnUpload_clicked\0"
    "on_btnRun_clicked\0on_btnVoltage_clicked\0"
    "on_btnMaxVoltage_clicked\0on_btnErrtol_clicked\0"
    "on_btnLineWidth_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lineWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lineWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        lineWidget *_t = static_cast<lineWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnLine_clicked(); break;
        case 1: _t->on_btnRect_clicked(); break;
        case 2: _t->on_btnEllipse_clicked(); break;
        case 3: _t->on_btnArcStart_clicked(); break;
        case 4: _t->on_btnArcSpan_clicked(); break;
        case 5: _t->on_btnArc_clicked(); break;
        case 6: _t->on_btnSave_clicked(); break;
        case 7: _t->on_btnClear_clicked(); break;
        case 8: _t->on_btnUpload_clicked(); break;
        case 9: _t->on_btnRun_clicked(); break;
        case 10: _t->on_btnVoltage_clicked(); break;
        case 11: _t->on_btnMaxVoltage_clicked(); break;
        case 12: _t->on_btnErrtol_clicked(); break;
        case 13: _t->on_btnLineWidth_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject lineWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_lineWidget.data,
      qt_meta_data_lineWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *lineWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lineWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lineWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lineWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
