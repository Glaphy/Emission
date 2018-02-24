#include "linewidget.h"
#include "ui_linewidget.h"

#include <cmath>
#include <QMouseEvent>
#include <QInputDialog>
#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>
#include <QString>
#include <QPoint>
#include <QLabel>

#define COLOUR 0

lineWidget::lineWidget(QWidget *parent) :
    QWidget(parent),ui(new Ui::lineWidget)
{



    ui->setupUi(this);
    mPix = QPixmap(350,350);
    mPix.fill(Qt::white);


    mousePressed = false;
    drawStarted = false;
    //default is line
    SelectedTool = 2;
    //Colouring variables
    NegVolts = 0;
    PosVolts=0;
    MaxVolts=5000;

    //Error tolerance variable
    Errvar= 0.01;

    //preset Arc angle values
    SpanAngle = 60*16;
    StartAngle = 150*16;

    //correction variable and shapes.
    Refresh=0;

    //fill shape radiobutton variable
    Fill=1;

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
        mEllipse.setTopLeft(event->pos());
        mEllipse.setBottomRight(event->pos());
    }
    else if (SelectedTool == 4){
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());
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
            mEllipse.setBottomRight(event->pos());
        }
        else if (SelectedTool ==4){
            mRect.setBottomRight(event->pos());
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
}


void lineWidget::paintEvent(QPaintEvent *event){

    painter.begin(this);
    if(!drawStarted){
        painter.drawPixmap(0,0,mPix);
    }
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
            painter.drawEllipse(mEllipse);
        }
        else if(SelectedTool == 4)
            painter.drawArc(mRect,StartAngle,SpanAngle);

        drawStarted = true;
    }
    else if (drawStarted && Refresh%2!=0){
        // It created a QPainter object by taking  a reference
        // to the QPixmap object created earlier, then draws a line
        // using that object, then sets the earlier painter object
        // with the newly modified QPixmap object


        //temporary painter is set with user defined fill and pen style
        //based on buttons.

        QPainter tempPainter(&mPix);
        QPen tempPen;
        tempPen.setWidth(Fill);
        tempPen.setBrush(QColor(PosVolts,NegVolts,0));

        if(ui->rbSetFill->isChecked()){
            tempPainter.setBrush(QBrush(QColor(PosVolts,NegVolts,0)));
        }
        else{
            tempPainter.setBrush(QBrush(QColor(255,255,255,0)));
        }
        tempPainter.setPen(tempPen);



        if(SelectedTool == 1){
            tempPainter.drawRect(mRect);
        }
        else if(SelectedTool == 2){

            tempPainter.drawLine(mLine);
        }
        else if(SelectedTool == 3){ 
            tempPainter.drawEllipse(mEllipse);
        }
        else if(SelectedTool == 4){
            tempPainter.drawArc(mRect,StartAngle,SpanAngle);
        }
        else if (SelectedTool == 5){
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
    }
    painter.end();
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

void lineWidget::on_btnErrtol_clicked(){
    //! [0]
        bool ok;
        double i = QInputDialog::getDouble(this, tr("Percentage Error tolerance for Method 1"),
                                     tr("Please input a float value (very small for good accuracy):"), 0,0, 100, 1, &ok);
        if (ok){
            Errvar = i;
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

void lineWidget::on_btnLineWidth_clicked(){
    //! [0]
        bool ok;
        int i = QInputDialog::getInt(this, tr("Line Width in Pixels"),
                                     tr("set Line width (and Shape outline):"),1, 0, 100000, 1, &ok);
        if (ok){
            Fill=i;
        }
    //! [0]
}

void lineWidget::on_btnArcStart_clicked(){
    //! [0]
        bool ok;
        int i = QInputDialog::getInt(this, tr("Set initial Arc Angle"),
                                     tr("Angle (degrees):"), StartAngle, 0, 360, 1, &ok);
        if (ok){
            StartAngle=i*16;
            }
    //! [0]
}

void lineWidget::on_btnArcSpan_clicked(){
    //! [0]
        bool ok;
        int i = QInputDialog::getInt(this, tr("Set Arc Span Angle over area drawn"),
                                     tr("Angle (degrees):"), SpanAngle, 0, 360, 1, &ok);
        if (ok){
            SpanAngle=i*16;
            }
    //! [0]
}

void lineWidget::on_btnRect_clicked()
{
    SelectedTool = 1;
}

void lineWidget::on_btnLine_clicked(){
    SelectedTool = 2;
}

void lineWidget::on_btnEllipse_clicked()
{
    SelectedTool = 3;
}

void lineWidget::on_btnArc_clicked()
{
    SelectedTool = 4;
}

void lineWidget::on_btnClear_clicked()
{

    SelectedTool = 5;
    mPix.fill(Qt::white);
    update();
}

void lineWidget::on_btnSave_clicked()
{
    QFile file("datpic.png");
    mPix.save(&file,"PNG",-1);
}

void lineWidget::on_btnUpload_clicked(){
    //! [0]
        bool ok;
        QString filename = QInputDialog::getText(this, tr("Upload PNG"),
                                     tr("Provide filename of PNG:"), QLineEdit::Normal, "", &ok);
        if (ok && !filename.isEmpty()){
            mPix.load(filename);
            QFile file("datpic.png");
            mPix.save(&file,"PNG",-1);

        }

    //! [0]
}

void lineWidget::on_btnRun_clicked(){
    extern int maxVolt;
    maxVolt = MaxVolts;

    extern double errtol;
    errtol = Errvar;

    extern int methodvar;
    methodvar=ui->MethodBox->currentIndex();

    if(ui->rbInF->isChecked()){
        extern bool inf;
        inf = true;
    }




    close();
}
