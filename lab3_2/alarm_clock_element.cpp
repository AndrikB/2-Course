#include "alarm_clock_element.h"
#include "ui_alarm_clock_element.h"

alarm_clock_element::alarm_clock_element(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alarm_clock_element)
{
    ui->setupUi(this);
}

alarm_clock_element::~alarm_clock_element()
{
    delete ui;
}

void alarm_clock_element::clock_bell()
{
    if (is_active)
        if (time.hour()==QTime::currentTime().hour()&&time.minute()==QTime::currentTime().minute())
        {
            is_active=false;
            if (not_disturb) return;
            sign =new bell;
            sign->setWindowTitle("ALARM");
            sign->show();

        }
}

void alarm_clock_element::sett()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(clock_bell()));
    timer->start();
}
