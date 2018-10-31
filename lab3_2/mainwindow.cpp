#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

const QString name="autosave.autosave";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->open(name);
    ui->setupUi(this);
    show_time();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this,SLOT(show_time()) );
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_time()
{
    QTime time= QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    if (time.second()%2==0){time_text[3]=' '; time_text[8]=' ';}
    ui->Digital_clock->setText(time_text);
    QDate date =QDate::currentDate();
    QString date_text=date.toString();
    ui->Digital_date->setText(date_text);
}


void MainWindow::on_Timer_clicked()
{
    timer.setWindowTitle("Timer");
    timer.show();
    timer.setFixedHeight(238);
    timer.setFixedWidth(528);
}

void MainWindow::on_Alarm_Clock_clicked()
{
    clock.setWindowTitle("Alarm clock");
    clock.show();
    clock.setFixedHeight(238);
    clock.setFixedWidth(641);
}

void MainWindow::on_notDisturm_stateChanged(int arg1)
{
    not_disturb=!not_disturb;
}

void MainWindow::save(QString name)
{
    QFile fout(name);
    fout.open(QIODevice::WriteOnly| QIODevice::Text);
    /*
     * struct of files
     * ----------------------
     * bool not disturb
     *
     * |timer|
     * size of timers
     * timer_element * count of timers
     *
     * size of list of list
     * {
     * mb size of name
     * name list of timer
     * size list timer
     * index list timer * count list timer
     * }*size of list of list
     *
     *  and this for alarm
     *
    */
    QTextStream out(&fout);

    out<<not_disturb<<endl;
    //|timer|
    int size_of_timers=this->timer.vec.size();
    out<<size_of_timers<<endl;
    for (int i=0;i<size_of_timers;i++)//timer_elements
    {
        out<<timer.vec[i]->time.toString("hh:mm:ss")<<endl
           <<timer.vec[i]->tmp.toString("hh:mm:ss")<<endl
           <<timer.vec[i]->is_active<<endl
           <<timer.vec[i]->is_not_pause<<endl;
    }

    int size_list_of_list_of_timers=this->timer.list_of_list.size();
    out<<size_list_of_list_of_timers<<endl;
    for (int i=0;i<size_list_of_list_of_timers;i++)//list of timer
    {
        int size_list_of_timer=timer.list_of_list[i]->V.size();
        out <<timer.list_of_list[i]->name<<endl
            <<size_list_of_timer<<endl;
        for (int j=0;j<size_list_of_timer;j++)
        {
            out<<timer.list_of_list[i]->V[j]<<endl;
        }
    }

    //|alarm|
    int size_of_alarm=this->clock.vec.size();
    out<<size_of_alarm<<endl;
    for(int i=0;i<size_of_alarm;i++)//alarm el
    {
        out<<clock.vec[i]->time.toString("hh:mm")<<endl
           <<clock.vec[i]->is_active<<endl;
    }

    int size_list_of_list_of_alarm=this->clock.list_of_list.size();
    out<<size_list_of_list_of_alarm<<endl;
    for (int i=0;i<size_list_of_list_of_alarm;i++)//list of alarm
    {
        int size_list_of_alarm=clock.list_of_list[i]->V.size();
        out <<clock.list_of_list[i]->name<<endl
            <<size_list_of_alarm<<endl;
        for (int j=0;j<size_list_of_alarm;j++)
        {
            out<<clock.list_of_list[i]->V[j]<<endl;
        }
    }

    fout.close();
}


void MainWindow::on_Save_as_clicked()
{
    QString name=QFileDialog::getSaveFileName(this,tr("Save File"),"" , "*.myfile");

    this->save(name);
}

void MainWindow::open(QString name)
{
    timer.list_of_list.clear();
    timer.vec.clear();
    clock.list_of_list.clear();
    clock.vec.clear();
    QFile fin(name);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    /*
     * struct of files
     * ----------------------
     * bool not disturb
     *
     * |timer|
     * size of timers
     * timer_element * count of timers
     *
     * size of list of list
     * {
     * name list of timer
     * size list timer
     * index list timer * count list timer
     * }*size of list of list
     *
     *  and this for alarm
     *
    */
    QTextStream in(&fin);
    not_disturb=in.readLine().toInt();

    //|timer|
    int size_of_timers=in.readLine().toInt();
    for (int i=0;i<size_of_timers;i++)//timer_elements
    {
        timer_element *tmp=new timer_element;
        tmp->time=time_from_str(in.readLine());

        tmp->tmp=time_from_str(in.readLine());

        tmp->is_active=in.readLine().toInt();

        tmp->is_not_pause=in.readLine().toInt();
        tmp->timer=new QTimer;
        if (tmp->is_active&&tmp->is_not_pause) {tmp->timer->start(tmp->time.msecsSinceStartOfDay());}
        timer.vec.push_back(tmp);
    }

    int size_of_list_of_list_of_timer=in.readLine().toInt();
    for (int i=0;i<size_of_list_of_list_of_timer;i++)//list of limer
    {

        list_timer *lt = new list_timer;
        lt->name=in.readLine();
        int size_of_list=in.readLine().toInt();
        for (int j=0;j<size_of_list;j++)
        {
            lt->V.push_back(in.readLine().toInt());
        }
        timer.list_of_list.push_back(lt);
    }

    //|alarm|
    int size_of_alarm=in.readLine().toInt();
    for (int i=0;i<size_of_alarm;i++)//alarm el
    {
        alarm_clock_element* ac=new alarm_clock_element;
        ac->time=alarm_from_str(in.readLine());
        ac->is_active=in.readLine().toInt();
        clock.vec.push_back(ac);
    }

    int size_of_list_of_list_of_alarm=in.readLine().toInt();
    for (int i=0;i<size_of_list_of_list_of_alarm;i++)//list of alarm
    {
        list_alarm * la= new list_alarm;
        la->name=in.readLine();
        int size_of_list=in.readLine().toInt();
        for (int j=0;j<size_of_list;j++)
        {
            la->V.push_back(in.readLine().toInt());
        }
        clock.list_of_list.push_back(la);
    }
}


void MainWindow::on_open_file_clicked()
{

    QString fileName =QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   "",
                                                   "*.myfile");
    //name
    this->open(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->clock.close();
    this->timer.close();
    this->save(name);
}

