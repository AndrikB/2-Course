#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
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
    timer = new Timer;
    timer->setWindowTitle("Timer");
    timer->show();

}

void MainWindow::on_Alarm_Clock_clicked()
{
    clock=new Alarm_Clock;
    clock->setWindowTitle("Alarm clock");
    clock->show();
}
