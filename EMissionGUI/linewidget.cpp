#include "linewidget.h"
#include "ui_linewidget.h"

#include <QMouseEvent>
#include <QPainter>


lineWidget::lineWidget(QWidget *parent) :
    QWidget(parent),ui(new Ui::lineWidget)
{
    ui->setupUi(this);
    mPix = QPixmap(400,400);
    mPix.fill(Qt::white);

    //set everything to false as nothing has started yet
    mousePressed = false;
    drawStarted = false;
    //default is line
    SelectedTool = 2;
}


void lineWidget::mousePressEvent(QMouseEvent* event){
    //Mouse is pressed for the first time
    mousePressed = true;

    //set the initial line points, both are same
    if(SelectedTool == 1){
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());
    }
    else if (SelectedTool == 2){
        mLine.setP1(event->pos());
        mLine.setP2(event->pos());
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
    }

    //it calls the paintEven() function continuously
    update();
}


void lineWidget::mouseReleaseEvent(QMouseEvent *event){

    //When mouse is released update for the one last time
    mousePressed = false;
    update();
}


void lineWidget::paintEvent(QPaintEvent *event){

    painter.begin(this);
    //When the mouse is pressed
    if(mousePressed){
        // we are taking QPixmap reference again and again
        //on mouse move and drawing a line again and again
        //hence the painter view has a feeling of dynamic drawing
        painter.drawPixmap(0,0,mPix);

        if(SelectedTool == 1)
            painter.drawRect(mRect);
        else if(SelectedTool == 2)
            painter.drawLine(mLine);

        drawStarted = true;
    }
    else if (drawStarted){
        // It created a QPainter object by taking  a reference
        // to the QPixmap object created earlier, then draws a line
        // using that object, then sets the earlier painter object
        // with the newly modified QPixmap object
        QPainter tempPainter(&mPix);
        if(SelectedTool == 1)
            tempPainter.drawRect(mRect);
        else if(SelectedTool == 2)
            tempPainter.drawLine(mLine);
        else if(SelectedTool == 3)
            tempPainter.fillRect(mRect,Qt::black);

        painter.drawPixmap(0,0,mPix);
    }
    painter.end();

}


lineWidget::~lineWidget()
{
    delete ui;
}

//Here we define what the button handles do.
void lineWidget::on_btnLine_clicked(){
        SelectedTool = 2;
}

void lineWidget::on_btnRect_clicked()
{
    SelectedTool = 1;
}

void lineWidget::on_btnSave_clicked()
{
    QFile file("datpic.bmp");
    //file.open(QIODevice::WriteOnly);
    mPix.save(&file,"BMP",-1);
    QCoreApplication::applicationFilePath();
}

void lineWidget::on_btnClear_clicked()
{
    //mPix = QPixmap(400,400);
    //mPix.fill(Qt::white);
    mPix = QPixmap(400,400);
    mPix.fill(Qt::white);
    painter.resetMatrix();
    SelectedTool = 3;
}
