#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#pragma once

#include <QPainter>
#include <QWidget>



/*
done
*/





namespace Ui {
    class lineWidget;
}

class lineWidget: public QWidget{

    Q_OBJECT

public:
    //the constructor is marked explicit so that we don't get any
    // implicit conversion by passing the wrong parameter
    //also it has a default null pointer value, so a linewidget can
    //be created with null parameter (i.e when we don't specify the
    //constructor parenthesis at all!)

    explicit lineWidget(QWidget *parent=0);
    bool mousePressed;
    bool drawStarted;
    int SelectedTool;
    int PosVolts;
    int NegVolts;
    int MaxVolts;

    //destructor is needed when we construct a object on the heap
    //instead of stack for efficient memory management
    ~lineWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_btnLine_clicked();
    void on_btnRect_clicked();
    void on_btnArc_clicked();

    void on_btnSave_clicked();
    void on_btnClear_clicked();

    void on_btnVoltage_clicked();
    void on_btnMaxVoltage_clicked();



private:
    //we declare a linewidget pointer object using namespace identifier;
    Ui::lineWidget *ui;
    QPainter painter;
    QPixmap mPix;

    QLine mLine;
    QRect mRect;
    QRect mArc;


};



#endif // LINEWIDGET_H
