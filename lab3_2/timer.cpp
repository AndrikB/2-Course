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
    bool b;
    int size=vec.size();//size all
    int timer_el=ui->listWidget->currentRow();//current item
    int list_el=-1;//current list
    list_el=ui->listWidget_2->currentRow();
    int size_list_of_list=list_of_list.size();
    int size_list=-1;//size current list
    if (list_el!=-1)size_list=list_of_list[list_el]->V.size();//size current list

    //list widget
    {
        //list of timer
        ui->listWidget->clear();
        for (int i=0;i<size;i++ )
        {
            QString s;
            for(int j=0;j<size_list;j++)
            {
                if (list_of_list[list_el]->V[j]==i)
                {
                    s=s+"+";
                    j=size_list;
                }
            }

            s=s+this->vec[i]->time.toString("hh:mm:ss   |->   ");
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

        //list of list
        ui->listWidget_2->clear();
        for (int i=0;i<size_list_of_list;i++)
        {
            ui->listWidget_2->addItem(list_of_list[i]->name);
        }
        ui->listWidget_2->setCurrentRow(list_el);
    }

    //buttons
    {
        //button "stop"/"start"
        if (timer_el==-1) ui->make_reverse->setVisible(false);
        else
        {
            ui->make_reverse->setVisible(true);
            if (vec[timer_el]->is_active)
            {
                ui->make_reverse->setText("Stop");
            }
            else
            {
                ui->make_reverse->setText("Start");
            }
        }

        //button "pause"/"continue"
        if (timer_el==-1||!vec[timer_el]->is_active) ui->pause_continue_button->setVisible(false);
        else
        {
            ui->pause_continue_button->setVisible(true);
            if (vec[timer_el]->is_not_pause)
            {
                ui->pause_continue_button->setText("Pause");
            }
            else
            {
                 ui->pause_continue_button->setText("Continue");
            }
        }

        //button "delete"
         if (timer_el==-1) ui->Delete->setVisible(false);
         else ui->Delete->setVisible(true);

        //button "del/add from list
         if (timer_el==-1||list_el==-1) ui->add_del_from_list->setVisible(false);
         else
         {
             b=false;//is here
             ui->add_del_from_list->setVisible(true);
             for (int i=0;i<size_list;i++)
             {
                 if (list_of_list[list_el]->V[i]==timer_el)
                    b=true;
             }
             if (b) ui->add_del_from_list->setText("Remove from list");
             else ui->add_del_from_list->setText("Add to list");

         }

         //button "del list"
         if (list_el==-1) ui->delete_list->setVisible(false);
         else ui->delete_list->setVisible(true);

        //button "pause list"
         if (list_el==-1) ui->pause_list->setVisible(false);
         else
         {
             ui->pause_list->setVisible(true);
             b=true;
             for (int i=0;i<size_list;i++)
             {
                 if (vec[list_of_list[list_el]->V[i]]->is_not_pause)
                     b=false;
             }
             if (b) ui->pause_list->setText("Pause list");
             else ui->pause_list->setText("Resume list");
         }

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
        vec[index]->timer->start(vec[index]->time.msecsSinceStartOfDay());
        vec[index]->is_active=true;
    }
}

void Timer::on_pause_continue_button_clicked()
{
    int index=ui->listWidget->currentRow();
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

void Timer::on_add_new_list_clicked()
{
    list_timer *list= new list_timer;
    list->name=QInputDialog::getText(this,"Name", "Write name of list:");
    //may be smth check
    list_of_list.push_back(list);
}

void Timer::on_add_del_from_list_clicked()
{
    int timer_el=ui->listWidget->currentRow();
    int list_el=ui->listWidget_2->currentRow();
    int size=list_of_list[list_el]->V.size();

    for (int i=0;i<size;i++)
    {
        if (list_of_list[list_el]->V[i]==timer_el)//if remove
        {
            list_of_list[list_el]->V.remove(i);
            return;
        }
    }
    //else
    list_of_list[list_el]->V.push_back(timer_el);
}

void Timer::on_delete_list_clicked()
{
     int list_el=ui->listWidget_2->currentRow();
     list_of_list.remove(list_el);
}

void Timer::on_pause_list_clicked()
{
    bool b=true;//true - all is active
    int  list_el=ui->listWidget_2->currentRow();//current list
    int size_list=list_of_list[list_el]->V.size();//size current list

    for (int i=0;i<size_list;i++)
    {
        if (vec[list_of_list[list_el]->V[i]]->is_not_pause)
            b=false;
    }

    if (b)
    {
        for (int i=0;i<size_list;i++)
        {
            int index =list_of_list[list_el]->V[i];

            int ms=vec[index]->timer->remainingTime();
            vec[index]->tmp.setHMS(ms/3600000, (ms/60000)%60,(ms%60000)/1000, ms%1000);;
            vec[index]->timer->stop();
            vec[index]->is_not_pause=false;
        }
    }
    else
    {
        for (int i=0;i<size_list;i++)
        {
            int index =list_of_list[list_el]->V[i];
            vec[index]->timer->start(vec[index]->tmp.msecsSinceStartOfDay());
            vec[index]->is_not_pause=true;
        }
    }
}
