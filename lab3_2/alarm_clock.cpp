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

void Alarm_Clock::set_time()
{

}

void Alarm_Clock::on_Start_alarm_clicked()
{
    st=QInputDialog::getText(this,"Time", "Write time");
    int h=st[0].digitValue()*10+st[1].digitValue();
    int m=st[3].digitValue()*10+st[4].digitValue();
    time.setHMS(h, m, 0);
    QString time_text=time.toString("hh:mm");
    ui->label->setText(time_text);
}
