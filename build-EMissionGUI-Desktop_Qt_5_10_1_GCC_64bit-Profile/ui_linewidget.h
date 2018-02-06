/********************************************************************************
** Form generated from reading UI file 'linewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEWIDGET_H
#define UI_LINEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lineWidget
{
public:
    QPushButton *pushButton;
    QSlider *horizontalSlider;

    void setupUi(QWidget *lineWidget)
    {
        if (lineWidget->objectName().isEmpty())
            lineWidget->setObjectName(QStringLiteral("lineWidget"));
        lineWidget->resize(623, 467);
        lineWidget->setProperty("save", QVariant(false));
        pushButton = new QPushButton(lineWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(530, 430, 84, 28));
        horizontalSlider = new QSlider(lineWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(460, 410, 160, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(lineWidget);
        QObject::connect(pushButton, SIGNAL(clicked()), lineWidget, SLOT(close()));
        QObject::connect(horizontalSlider, SIGNAL(actionTriggered(int)), lineWidget, SLOT(repaint()));

        QMetaObject::connectSlotsByName(lineWidget);
    } // setupUi

    void retranslateUi(QWidget *lineWidget)
    {
        lineWidget->setWindowTitle(QApplication::translate("lineWidget", "lineWidget", nullptr));
        pushButton->setText(QApplication::translate("lineWidget", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lineWidget: public Ui_lineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEWIDGET_H
