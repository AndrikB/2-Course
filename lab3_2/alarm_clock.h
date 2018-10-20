#ifndef ALARM_CLOCK_H
#define ALARM_CLOCK_H
#include "timer.h"

#include "alarm_clock_element.h"


struct list_alarm
{
    QVector<int> V;
    QString name;
};

namespace Ui {
class Alarm_Clock;
}

class Alarm_Clock : public QDialog
{
    Q_OBJECT

public:
    explicit Alarm_Clock(QWidget *parent = nullptr);
    ~Alarm_Clock();

    void set_time();
private slots:
    void on_Start_alarm_clicked();
    void write_list();

    void on_opposition_clicked();

    void on_Delete_clicked();

    void on_add_new_list_clicked();

    void on_delete_list_clicked();

    void on_remove_add_from_list_clicked();

    void on_pause_continue_List_clicked();


private:
    Ui::Alarm_Clock *ui;
    QVector<alarm_clock_element*> vec;
    QVector<list_alarm*> list_of_list;

};

#endif // ALARM_CLOCK_H
