#include "linewidget.h"
#include "ui_linewidget.h"

#include <cmath>
#include <QMouseEvent>
#include <QInputDialog>
#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>

#include <QPoint>

#define COLOUR 0



lineWidget::lineWidget(QWidget *parent) :
    QWidget(parent),ui(new Ui::lineWidget)
{
    ui->setupUi(this);
    mPix = QPixmap(400,400);
    mPix.fill(Qt::white);
    //mPix.load("datdrawing.png");


    mousePressed = false;
    drawStarted = false;
    //default is line
    SelectedTool = 2;
    //Colouring variables
    NegVolts = 0;
    PosVolts=0;
    MaxVolts=5000;

    //correction variable and shapes.
    Refresh=0;

    QPoint p(500,500);
    QPoint q(550,550);

    offRect.setTopLeft(p);
    offRect.setBottomLeft(q);

}



void lineWidget::mousePressEvent(QMouseEvent* event){
    //Mouse is pressed for the first time
    mousePressed = true;

    //set the initial line points, both are same
    if(SelectedTool == 1){
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());
    }
    else if (SelectedTool == 2 ){
        mLine.setP1(event->pos());
        mLine.setP2(event->pos());
    }
    else if (SelectedTool == 3){
        mArc.setTopLeft(event->pos());
        mArc.setBottomRight(event->pos());
    }
}



void lineWidget::mouseMoveEvent(QMouseEvent* event){

    //As mouse is moving set the second point again and again
    // and update continuously

    if(event->type() == QEvent::MouseMove){
        if(SelectedTool == 1){
            mRect.setBottomRight(event->pos());
        }
        else if (SelectedTool == 2){
            mLine.setP2(event->pos());
        }
        else if (SelectedTool == 3){
            mArc.setBottomRight(event->pos());
        }

    }

    //it calls the paintEvent() function continuously
    update();
}


void lineWidget::mouseReleaseEvent(QMouseEvent *event){

    //When mouse is released update for the one last time
    mousePressed = false;
    update();
    Refresh=Refresh+1;
    //update();
    //Refresh= Refresh+1;
}


void lineWidget::paintEvent(QPaintEvent *event){

    //mPix.load("datdrawing.png");



    painter.begin(this);
    //When the mouse is pressed
    if(mousePressed){
        // we are taking QPixmap reference again and again
        //on mouse move and drawing a line again and again
        //hence the painter view has a feeling of dynamic drawing
        painter.drawPixmap(0,0,mPix);


        if(SelectedTool == 1){
            painter.drawRect(mRect);
        }
        else if(SelectedTool == 2){
            painter.drawLine(mLine);
        }
        else if(SelectedTool == 3){
            painter.drawEllipse(mArc);
        }

        drawStarted = true;
    }
    else if (drawStarted && Refresh%2!=0){
        // It created a QPainter object by taking  a reference
        // to the QPixmap object created earlier, then draws a line
        // using that object, then sets the earlier painter object
        // with the newly modified QPixmap object
        QPainter tempPainter(&mPix);

        tempPainter.setPen(QPen(QColor(PosVolts,NegVolts,0)));
        tempPainter.setBrush(QBrush(QColor(PosVolts,NegVolts,0)));

        if(SelectedTool == 1){
            //int startangle = 180*16;
            //int spanangle = 120*16;
            //tempPainter.drawArc(mRect,startangle,spanangle);
            tempPainter.drawRect(mRect);
        }
        else if(SelectedTool == 2){

            tempPainter.drawLine(mLine);
        }
        else if(SelectedTool == 3){ 
            tempPainter.drawEllipse(mArc);
        }
        else if (SelectedTool == 4){
            mPix.fill(Qt::white);
        }

        tempPainter.setPen(QPen(Qt::black));
        tempPainter.setBrush(QBrush(Qt::white));
        painter.drawPixmap(0,0,mPix);
        Refresh = Refresh + 1;

    }

    if (drawStarted && Refresh%2==0){
        QPainter offPainter(&mPix);

        offPainter.setPen(QPen(QColor(PosVolts,NegVolts,0)));

        offPainter.drawRect(offRect);
        painter.drawPixmap(0,0,mPix);
    }



    painter.end();
    //mousePressed = false;

//    painter.begin(this);
//    if (drawStarted && mousePressed == false){
//        painter.drawPixmap(0,0,mPix);
//        painter.drawRect(offRect);

//    }
//    painter.end();










    //QFile file("datdrawing.png");
    //mPix.save(&file,"PNG",-1);
    //mPix.load("datdrawing.png");
}


lineWidget::~lineWidget()
{
    delete ui;
}






//Here we define what the button handles do.

void lineWidget::on_btnVoltage_clicked(){
    //! [0]
        bool ok;
        int i = QInputDialog::getInt(this, tr("Voltage Colour"),
                                     tr("set Voltage Colour (integer):"), 0, -MaxVolts, MaxVolts, 1, &ok);
        if (ok){
            if (i<0){
                NegVolts=round(((float)i*255*(-1))/MaxVolts);
                PosVolts=0;
            }
            else{
                PosVolts=round(((float)i*255)/MaxVolts);
                NegVolts=0;
            }
        }

    //! [0]
}


void lineWidget::on_btnMaxVoltage_clicked(){
    //! [0]
        bool ok;
        MaxVolts = QInputDialog::getInt(this, tr("Voltage Colour"),
                                     tr("set Voltage Colour (integer):"), 0, -500000, 500000, 1, &ok);
    //! [0]
}


void lineWidget::on_btnLine_clicked(){
        SelectedTool = 2;
}

void lineWidget::on_btnRect_clicked()
{
    SelectedTool = 1;
}

void lineWidget::on_btnArc_clicked()
{
    SelectedTool = 3;
    //void QPainter::drawArc(100,199,59,39,79,78)
}

void lineWidget::on_btnSave_clicked()
{
    QFile file("datpic.png");
    //file.open(QIODevice::WriteOnly);
    mPix.save(&file,"PNG",-1);
}

void lineWidget::on_btnClear_clicked()
{

    SelectedTool = 4;
    update();
}
