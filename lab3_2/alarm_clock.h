#ifndef ALARM_CLOCK_H
#define ALARM_CLOCK_H
#include "timer.h"

#include "alarm_clock_element.h"
#include <QInputDialog>

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


    void on_rewrite_clicked();

    void on_opposition_clicked();

    void on_Delete_clicked();

private:
    Ui::Alarm_Clock *ui;
    QVector<alarm_clock_element*> vec;
};

#endif // ALARM_CLOCK_H
