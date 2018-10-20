#include "alarm_clock.h"
#include "ui_alarm_clock.h"

Alarm_Clock::Alarm_Clock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alarm_Clock)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(write_list()) );
    timer->start(200);
}

Alarm_Clock::~Alarm_Clock()
{
    delete ui;
}

void Alarm_Clock::on_Start_alarm_clicked()
{

    QString st=QInputDialog::getText(this,"Time", "Write time");
    for (int i=0;i<=4;i++)
    {
        if (i==2) i++;
        if (!st[i].isDigit()) return;
    }
    //if (st[2]!=':') return;
    int h=st[0].digitValue()*10+st[1].digitValue();
    int m=st[3].digitValue()*10+st[4].digitValue();
    alarm_clock_element *tmp= new alarm_clock_element;
    tmp->time.setHMS(h, m, 0);
    if (tmp->time.isNull()) return;
    vec.push_back(tmp);
    tmp->sett();
}

//T1>T2
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
    int size=vec.size();//size main list
    int size_list_of_list=list_of_list.size();
    int alarm_el=ui->listWidget->currentRow();//current item
    int list_el=-1;//current list
    list_el=ui->listWidget_2->currentRow();
    int size_list=NULL;//size of current list
    if (list_el!=-1)size_list=list_of_list[list_el]->V.size();

    ui->listWidget->clear();
    for (int i=0;i<size;i++ )
    {
        QString s;
        for (int j=0;j<size_list;j++)
            if (list_of_list[list_el]->V[j]==i)
            {
                s=s+"+";
                j=size_list;
            //if it may be colour cout
            }
        s=s+vec[i]->time.toString("hh : mm     |->   ");
        if (!vec[i]->is_active) s=s+"NULL";
        else
        {
            QTime tmp=time_diference(vec[i]->time, QTime::currentTime());
            s=s+tmp.toString("hh:mm:ss");
        }
        ui->listWidget->addItem(s);
    }
    ui->listWidget->setCurrentRow(alarm_el);

    ui->listWidget_2->clear();
    for (int i=0;i<size_list_of_list;i++)
    {
        ui->listWidget_2->addItem(list_of_list[i]->name);
    }
    ui->listWidget_2->setCurrentRow(list_el);
}

void Alarm_Clock::on_opposition_clicked()
{
    int i=ui->listWidget->currentRow();
    vec[i]->is_active=!vec[i]->is_active;
}

void Alarm_Clock::on_Delete_clicked()//delete_alarm
{
    int i=ui->listWidget->currentRow();
    if (i<0||i>vec.size()) return;
    vec.remove(i);
    this->write_list();
}



void Alarm_Clock::on_add_new_list_clicked()
{
    list_alarm *list= new list_alarm;
    list->name=QInputDialog::getText(this,"Name", "Write name of list:");
    qDebug()<<list->V.empty();
    //may be smth check
    list_of_list.push_back(list);
}

void Alarm_Clock::on_Add_to_list_clicked()
{
    int alarm_el=ui->listWidget->currentRow();
    int list_el=ui->listWidget_2->currentRow();
    int size =list_of_list[list_el]->V.size();
    for (int i=0;i<size;i++)
        if (list_of_list[list_el]->V[i]==alarm_el) return;
    list_of_list[list_el]->V.push_back(alarm_el);
}

void Alarm_Clock::on_delete_list_clicked()
{
     int list_el=ui->listWidget_2->currentRow();
     list_of_list.remove(list_el);
}

void Alarm_Clock::on_remove_from_list_clicked()
{
    int alarm_el=ui->listWidget->currentRow();
    int list_el=ui->listWidget_2->currentRow();
    int size =list_of_list[list_el]->V.size();
    for (int i=0;i<size;i++)
    {
        if (list_of_list[list_el]->V[i]==alarm_el)
        {
            list_of_list[list_el]->V.remove(i);
            return;
        }
    }
}
