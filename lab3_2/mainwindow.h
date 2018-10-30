#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "alarm_clock.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Timer_clicked();
    void on_Alarm_Clock_clicked();
    void show_time();

    void on_notDisturm_stateChanged(int arg1);

    void on_Save_as_clicked();
    void save(QString name);

    void on_open_file_clicked();
    void open(QString name);

    void closeEvent(QCloseEvent *event)override;
private:
    Ui::MainWindow *ui;
    Timer timer;
    Alarm_Clock clock;
};

#endif // MAINWINDOW_H
