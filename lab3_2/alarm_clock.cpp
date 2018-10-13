#include "alarm_clock.h"
#include "ui_alarm_clock.h"


Alarm_Clock::Alarm_Clock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alarm_Clock)
{
    //ui->Start_alarm->setEnabled(1);
    ui->setupUi(this);

}

Alarm_Clock::~Alarm_Clock()
{
    delete ui;
}

void Alarm_Clock::on_Start_alarm_clicked()
{
    st=QInputDialog::getText(this,"Time", "Write time");
    int h=st[0].digitValue()*10+st[1].digitValue();
    int m=st[3].digitValue()*10+st[4].digitValue();
    time.setHMS(h, m, 0);
    QString time_text=time.toString("hh:mm:ss");
    ui->label->setText(time_text);
    QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(clock_bell()));
    timer->start();
}

void Alarm_Clock::clock_bell()
{
    if (is_active)
        if (time.hour()==QTime::currentTime().hour()&&time.minute()==QTime::currentTime().minute())
        {
            is_active=false;
            sign.setWindowTitle("ALARM");
            sign.show();
        }
}
