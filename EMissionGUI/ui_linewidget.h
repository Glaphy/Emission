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
#include <QRadioButton>
#include <QGroupBox>
#include <QObject>

QT_BEGIN_NAMESPACE

class Ui_lineWidget{
public:
    //DEFINE WIDGET POINTERS (GUI SPACE)
    QWidget *widget;
    QWidget *widgetArc;
    QWidget *RadioWidget;
    QWidget *InfWidget;
    QWidget *widgetSave;
    QWidget *widgetClear;
    QWidget *widgetUpload;
    QWidget *widgetRun;
    QWidget *widgetVoltage;
    QWidget *widgetMaxVoltage;
    QWidget *widgetErrtol;
    QWidget *widgetLineWidth;
    QDialog *widgetDialogue;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *RadioLayout;
    QVBoxLayout *InfLayout;

    //POINTER TO Voltage & tolerance BUTTONS
    QPushButton *btnVoltage;
    QPushButton *btnMaxVoltage;
    QPushButton *btnErrtol;

    //POINTER TO LINEWIDTH BUTTON
    QPushButton *btnLineWidth;

    //POINTER TO RADIO BUTTON
    QRadioButton *rbSetFill;

    //POINTER TO INF RADIO BUTTON
    QRadioButton *rbInF;

    //POINTERS TO ARC SETTINGS & BUTTON
    QPushButton *btnArcStart;
    QPushButton *btnArcSpan;
    QPushButton *btnArc;

    //POINTERS TO SHAPES HERE
    QPushButton *btnLine;
    QPushButton *btnRect;
    QPushButton *btnEllipse;

    //POINTERS TO OTHER BUTTONS
    QPushButton *btnSave;
    QPushButton *btnClear;
    QPushButton *btnUpload;
    QPushButton *btnRun;






    void setupUi(QWidget *lineWidget){
        if (lineWidget->objectName().isEmpty())
            lineWidget->setObjectName(QStringLiteral("lineWidget"));

        lineWidget->resize(730, 406);

        widgetVoltage= new QWidget(lineWidget);
        widgetVoltage->setObjectName(QStringLiteral("widgetVoltage"));
        widgetVoltage->setGeometry(QRect(610, 10, 100, 100));

        widgetMaxVoltage= new QWidget(lineWidget);
        widgetMaxVoltage->setObjectName(QStringLiteral("widgetVoltage"));
        widgetMaxVoltage->setGeometry(QRect(410, 10, 200, 100));

        widgetErrtol= new QWidget(lineWidget);
        widgetErrtol->setObjectName(QStringLiteral("widgetVoltage"));
        widgetErrtol->setGeometry(QRect(410, 60, 200, 100));

        widgetLineWidth= new QWidget(lineWidget);
        widgetLineWidth->setObjectName(QStringLiteral("widgetVoltage"));
        widgetLineWidth->setGeometry(QRect(600, 60, 200, 30));

        widgetClear= new QWidget(lineWidget);
        widgetClear->setObjectName(QStringLiteral("widgetClear"));
        widgetClear->setGeometry(QRect(410, 320, 100, 100));

        widgetSave = new QWidget(lineWidget);
        widgetSave->setObjectName(QStringLiteral("widgetSave"));
        widgetSave->setGeometry(QRect(410, 350, 100, 100));

        widgetUpload = new QWidget(lineWidget);
        widgetUpload->setObjectName(QStringLiteral("widgetUpload"));
        widgetUpload->setGeometry(QRect(610, 320, 100, 100));

        widgetRun = new QWidget(lineWidget);
        widgetRun->setObjectName(QStringLiteral("widgerRun"));
        widgetRun->setGeometry(QRect(610, 350, 100, 100));

        widget = new QWidget(lineWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(410, 150, 100, 100));

        widgetArc = new QWidget(lineWidget);
        widgetArc->setObjectName(QStringLiteral("widgetArc"));
        widgetArc->setGeometry(QRect(605, 150, 100, 100));

        //Vertical layout for Line,Rectangle,Ellipse
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(0,40,0,0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        btnLine = new QPushButton(widget);
        btnLine->setObjectName(QStringLiteral("btnLine"));

        btnRect = new QPushButton(widget);
        btnRect->setObjectName(QStringLiteral("btnRect"));
        verticalLayout->addWidget(btnRect);

        btnEllipse = new QPushButton(widget);
        btnEllipse->setObjectName(QStringLiteral("btnEllipse"));
        verticalLayout->addWidget(btnEllipse);

        //Vertical layout for Arc settings and Arc button
        verticalLayout = new QVBoxLayout(widgetArc);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(0,40,0,0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        btnArcStart = new QPushButton(widgetArc);
        btnArcStart->setObjectName(QStringLiteral("btnArcStart"));

        btnArcSpan = new QPushButton(widgetArc);
        btnArcSpan->setObjectName(QStringLiteral("btnArcSpan"));
        verticalLayout->addWidget(btnArcSpan);

        btnArc = new QPushButton(widgetArc);
        btnArc->setObjectName(QStringLiteral("btnArc"));
        verticalLayout->addWidget(btnArc);

        // Radio button defined here
        RadioWidget = new QWidget(lineWidget);
        RadioWidget->setObjectName(QStringLiteral("RadioWidget"));
        RadioWidget->setGeometry(QRect(410,110,100,30));

        RadioLayout = new QVBoxLayout(RadioWidget);
        RadioLayout->setContentsMargins(0,0,0,0);
        RadioLayout->setObjectName(QStringLiteral("RadioLayout"));

        rbSetFill = new QRadioButton(RadioWidget);
        rbSetFill->setAutoExclusive(false);
        rbSetFill->setChecked(false);
        rbSetFill->setObjectName(QStringLiteral("rbSetFill"));

        // Radio button for infinte toggle
        InfWidget = new QWidget(lineWidget);
        InfWidget->setObjectName(QStringLiteral("InfWidget"));
        InfWidget->setGeometry(QRect(410,280,100,30));

        InfLayout = new QVBoxLayout(InfWidget);
        InfLayout->setContentsMargins(0,0,0,0);
        InfLayout->setObjectName(QStringLiteral("InfLayout"));

        rbInF = new QRadioButton(InfWidget);
        rbInF->setAutoExclusive(false);
        rbInF->setChecked(false);
        rbInF->setObjectName(QStringLiteral("rbInf"));



        // Other stand alone buttons
        btnSave = new QPushButton(widgetSave);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        btnClear = new QPushButton(widgetClear);
        btnClear->setObjectName(QStringLiteral("btnClear"));

        btnUpload = new QPushButton(widgetUpload);
        btnUpload->setObjectName(QStringLiteral("btnUpload"));

        btnRun = new QPushButton(widgetRun);
        btnRun->setObjectName(QStringLiteral("btnRun"));

        btnVoltage = new QPushButton(widgetVoltage);
        btnVoltage->setObjectName(QStringLiteral("btnVoltage"));

        btnMaxVoltage = new QPushButton(widgetMaxVoltage);
        btnMaxVoltage->setObjectName(QStringLiteral("btnMaxVoltage"));

        btnErrtol= new QPushButton(widgetErrtol);
        btnErrtol-> setObjectName(QStringLiteral("btnErrtol"));

        btnLineWidth = new QPushButton(widgetLineWidth);
        btnLineWidth->setObjectName(QStringLiteral("btnLineWidth"));


        retranslateUi(lineWidget);

        QMetaObject::connectSlotsByName(lineWidget);
    }//Interface Setup.


    /* This names all the buttons*/
    void retranslateUi(QWidget *lineWidget){
        lineWidget->setWindowTitle(QApplication::translate("lineWidget","EMission GUI",0));
        btnLine->setText(QApplication::translate("lineWidget","Line",0));
        btnArcStart->setText(QApplication::translate("lineWidget","Arc Start angle",0));
        btnArcSpan->setText(QApplication::translate("lineWidget","Arc Span angle",0));
        btnArc->setText(QApplication::translate("lineWidget","Arc",0));
        btnRect->setText(QApplication::translate("lineWidget","Rectangle",0));
        btnSave->setText(QApplication::translate("lineWidget","Save",0));
        btnRun->setText(QApplication::translate("lineWidget","Run",0));
        btnUpload->setText(QApplication::translate("lineWidget","Upload",0));
        btnClear->setText(QApplication::translate("lineWidget","Clear",0));
        btnEllipse->setText(QApplication::translate("lineWidget","Ellipse",0));
        btnVoltage->setText(QApplication::translate("lineWidget","set Voltage",0));
        btnMaxVoltage->setText(QApplication::translate("lineWidget","set MaxVoltage",0));
        btnErrtol->setText(QApplication::translate("linewidget","Error Tolerance",0));
        btnLineWidth->setText(QApplication::translate("lineWidget","Set Line Width",0));
        rbSetFill->setText(QApplication::translate("lineWidget","Charge Fill",0));
        rbInF->setText(QApplication::translate("lineWidget","Infinite plates",0));
    } //RETRANSLATE UI
};

namespace Ui {
    class lineWidget: public Ui_lineWidget{};
} // namespace Ui

QT_END_NAMESPACE

#endif // LINEWIDGET_H
