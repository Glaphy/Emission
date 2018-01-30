#include "linewidget.h"
#include "ui_linewidget.h"

lineWidget::lineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lineWidget)
{
    ui->setupUi(this);
}

lineWidget::~lineWidget()
{
    delete ui;
}
