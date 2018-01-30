#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>

namespace Ui {
class lineWidget;
}

class lineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit lineWidget(QWidget *parent = 0);
    ~lineWidget();

private:
    Ui::lineWidget *ui;
};

#endif // LINEWIDGET_H
