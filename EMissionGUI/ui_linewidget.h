#ifndef UI_LINEWIDGET_H
#define UI_LINEWIDGET_H


#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QWidget>
#include <QDialog>

QT_BEGIN_NAMESPACE

class Ui_lineWidget{
public:
    //DEFINE WIDGET POINTERS (GUI SPACE)
    QWidget *widget;
    QWidget *widgetSave;
    QWidget *widgetClear;
    QWidget *widgetVoltage;
    QWidget *widgetMaxVoltage;
    QDialog *widgetDialogue;
    QVBoxLayout *verticalLayout;

    //POINTERS TO SHAPES HERE
    QPushButton *btnLine;
    QPushButton *btnRect;
    QPushButton *btnArc;

    //POINTERS TO OTHER BUTTONS
    QPushButton *btnSave;
    QPushButton *btnClear;

    //POINTER TO Voltage BUTTON
    QPushButton *btnVoltage;
    QPushButton *btnMaxVoltage;




    void setupUi(QWidget *lineWidget){
        if (lineWidget->objectName().isEmpty())
            lineWidget->setObjectName(QStringLiteral("lineWidget"));

        lineWidget->resize(717, 406);

        widget = new QWidget(lineWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(410, 200, 100, 100));

        widgetClear= new QWidget(lineWidget);
        widgetClear->setObjectName(QStringLiteral("widgetClear"));
        widgetClear->setGeometry(QRect(410, 320, 100, 100));

        widgetVoltage= new QWidget(lineWidget);
        widgetVoltage->setObjectName(QStringLiteral("widgetVoltage"));
        widgetVoltage->setGeometry(QRect(610, 10, 100, 100));

        widgetMaxVoltage= new QWidget(lineWidget);
        widgetMaxVoltage->setObjectName(QStringLiteral("widgetVoltage"));
        widgetMaxVoltage->setGeometry(QRect(410, 10, 200, 100));

        widgetSave = new QWidget(lineWidget);
        widgetSave->setObjectName(QStringLiteral("widgetSave"));
        widgetSave->setGeometry(QRect(410, 350, 100, 100));


        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(010);
        verticalLayout->setContentsMargins(0,40,0,0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));


        btnLine = new QPushButton(widget);
        btnLine->setObjectName(QStringLiteral("btnLine"));



        btnRect = new QPushButton(widget);
        btnRect->setObjectName(QStringLiteral("btnRect"));
        verticalLayout->addWidget(btnRect);


        btnArc = new QPushButton(widget);
        btnArc->setObjectName(QStringLiteral("btnArc"));
        verticalLayout->addWidget(btnArc);

        btnSave = new QPushButton(widgetSave);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        btnClear = new QPushButton(widgetClear);
        btnClear->setObjectName(QStringLiteral("btnClear"));

        btnVoltage = new QPushButton(widgetVoltage);
        btnVoltage->setObjectName(QStringLiteral("btnVoltage"));

        btnMaxVoltage = new QPushButton(widgetMaxVoltage);
        btnMaxVoltage->setObjectName(QStringLiteral("btnMaxVoltage"));


        retranslateUi(lineWidget);

        QMetaObject::connectSlotsByName(lineWidget);
    }//Interface Setup.


    /* This names all the buttons*/
    void retranslateUi(QWidget *lineWidget){
        lineWidget->setWindowTitle(QApplication::translate("lineWidget","EMission GUI",0));
        btnLine->setText(QApplication::translate("lineWidget","Line",0));
        btnRect->setText(QApplication::translate("lineWidget","Rectangle",0));
        btnSave->setText(QApplication::translate("lineWidget","Save",0));
        btnClear->setText(QApplication::translate("lineWidget","Clear",0));
        btnArc->setText(QApplication::translate("lineWidget","Arc",0));
        btnVoltage->setText(QApplication::translate("lineWidget","set Voltage",0));
        btnMaxVoltage->setText(QApplication::translate("lineWidget","set MaxVoltage",0));
    } //RETRANSLATE UI
};

namespace Ui {
    class lineWidget: public Ui_lineWidget{};
} // namespace Ui

QT_END_NAMESPACE

#endif // LINEWIDGET_H
