#include "timer_element.h"
#include "ui_timer_element.h"

timer_element::timer_element(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timer_element)
{
    ui->setupUi(this);
}

timer_element::~timer_element()
{
    delete ui;
}

void timer_element::clock_bell()
{
    if (is_active)
        {
            is_active=false;
            if (not_disturb) return;
            sign =new bell;
            sign->setWindowTitle("GET UP");
            sign->setFixedHeight(30);
            sign->setFixedWidth(170);
            sign->show();

        }
}

void timer_element::sett()
{

    connect(this->timer, SIGNAL(timeout()), this, SLOT(clock_bell()));

}
