#include "alarm_clock.h"
#include "ui_alarm_clock.h"

Alarm_Clock::Alarm_Clock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alarm_Clock)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(write_list()) );
    timer->start(100);
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

QTime time_diference(QTime T1, QTime T2)
{
    int h, m ,s;
    h=T1.hour()-T2.hour();
    m=T1.minute()-T2.minute();
    s=T1.second()-T2.second();
    while (s<0)
    {
        s+=60;
        m-=1;
    }
    while (m<0)
    {
        m+=60;
        h-=1;
    }
    while (h<0)h+=24;
    QTime tmp;
    tmp.setHMS(h, m,s);
    return tmp;
}

void Alarm_Clock::write_list()
{
    int size=vec.size();
    ui->listWidget->clear();
    for (int i=0;i<size;i++ ){
        QChar b;
        if (vec[i]->is_active)b='+';
        else b='-';
        QString s=vec[i]->time.toString("hh : mm     |->   ");
        if (!vec[i]->is_active) s=s+"NULL";
        else
        {
            QTime tmp=time_diference(vec[i]->time, QTime::currentTime());
            s=s+tmp.toString("hh:mm:ss");
        }
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
