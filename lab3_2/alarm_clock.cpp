#include "alarm_clock.h"
#include "ui_alarm_clock.h"

Alarm_Clock::Alarm_Clock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alarm_Clock)
{
    ui->setupUi(this);
}

Alarm_Clock::~Alarm_Clock()
{
    delete ui;
}

void Alarm_Clock::on_Start_alarm_clicked()
{

    QString st=QInputDialog::getText(this,"Time", "Write time");

    int h=st[0].digitValue()*10+st[1].digitValue();
    int m=st[3].digitValue()*10+st[4].digitValue();
    alarm_clock_element *tmp= new alarm_clock_element;
    tmp->time.setHMS(h, m, 0);
    if (tmp->time.isNull()) return;
    vec.push_back(tmp);
    tmp->sett();
    this->write_list();
}

void Alarm_Clock::write_list()
{
    int size=vec.size();
    ui->listWidget->clear();
    for (int i=0;i<size;i++ ){
        QChar b;
        if (vec[i]->is_active)b='+';
        else b='-';
        QString s=b+vec[i]->time.toString("hh : mm");
        ui->listWidget->addItem(s);
    }
}

void Alarm_Clock::on_rewrite_clicked()
{
    this->write_list();
}

void Alarm_Clock::on_opposition_clicked()
{
    int i=ui->listWidget->currentRow();
    if (i<0||i>vec.size()) return;
    vec[i]->is_active-=1;
    this->write_list();
}

void Alarm_Clock::on_Delete_clicked()
{
    int i=ui->listWidget->currentRow();
    if (i<0||i>vec.size()) return;
    vec.remove(i);
    this->write_list();
}
