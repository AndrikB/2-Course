#include "timer.h"
#include "ui_timer.h"
Timer::Timer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(write_list()) );
    timer->start(300);
}

Timer::~Timer()
{
    delete ui;
}

void Timer::write_list()
{
    //list widget
    int size=vec.size();
    int timer_el=-1;
    timer_el=ui->listWidget->currentRow();
    ui->listWidget->clear();
    for (int i=0;i<size;i++ )
    {
        QString s;
        s=this->vec[i]->time.toString("hh:mm:ss   |->   ");
        if (vec[i]->is_active)
        {
            if (vec[i]->is_not_pause)
            {
                int ms=vec[i]->timer->remainingTime();
                QTime tmp;
                tmp.setHMS(ms/3600000, (ms/60000)%60,(ms%60000)/1000, ms%1000);
                s=s+tmp.toString("h:m:s:z");
            }
            else
            {
                s=s+vec[i]->tmp.toString("h:m:s:z");
            }
        }
        else s=s+"NULL";
        ui->listWidget->addItem(s);
    }
    ui->listWidget->setCurrentRow(timer_el);

    //buttons

    //button "stop"/"start"
    if (timer_el==-1)return;
    if (vec[timer_el]->is_active)
    {
        ui->make_reverse->setText("Stop");
    }
    else
    {
        ui->make_reverse->setText("Start");
    }
    if (vec[timer_el]->is_not_pause)
    {
        ui->pause_continue_button->setText("Pause");
    }
    else
    {
         ui->pause_continue_button->setText("Continue");
    }

}

void Timer::on_add_new_clicked()
{

    QString st=QInputDialog::getText(this,"Time", "Write time");
    for (int i=0;i<=7;i++)
    {
        if (i==2||i==5) i++;
        if (!st[i].isDigit()) {return; }
    }
    if (st[2]!=':'||st[5]!=':') return;
    timer_element *timer = new timer_element;
    int h=st[0].digitValue()*10+st[1].digitValue();
    int m=st[3].digitValue()*10+st[4].digitValue();
    int s=st[6].digitValue()*10+st[7].digitValue();
    timer->timer=new QTimer;
    timer->time.setHMS(h, m, s);
    if (timer->time.isNull()) return;
    timer->timer->start(timer->time.msecsSinceStartOfDay());
    timer->sett();
    vec.push_back(timer);
}

void Timer::on_make_reverse_clicked()//stop
{
    int index=-1;
    index=ui->listWidget->currentRow();
    if (index==-1)return;
    if (vec[index]->is_active)
    {
        vec[index]->timer->stop();
        vec[index]->is_active=false;
    }
    else
    {
        vec[index]->timer->start();
        vec[index]->is_active=true;
    }
}

void Timer::on_pause_continue_button_clicked()
{
    int index=-1;
    index=ui->listWidget->currentRow();
    if (index==-1)return;
    if (vec[index]->is_not_pause)
    {
        int ms=vec[index]->timer->remainingTime();
        vec[index]->tmp.setHMS(ms/3600000, (ms/60000)%60,(ms%60000)/1000, ms%1000);;

        vec[index]->timer->stop();
        vec[index]->is_not_pause=false;
    }
    else
    {
        vec[index]->timer->start(vec[index]->tmp.msecsSinceStartOfDay());
        vec[index]->is_not_pause=true;
    }
}

void Timer::on_Delete_clicked()
{
    int index=-1;
    index=ui->listWidget->currentRow();
    if (index==-1)return;
    vec.remove(index);
}
