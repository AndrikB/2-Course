#ifndef ALARM_CLOCK_H
#define ALARM_CLOCK_H
#include <QDateTime>
#include <QDialog>
#include <QInputDialog>
#include "timer.h"
#include "bell.h"
#include <QTimer>

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
    void clock_bell();

private:
    Ui::Alarm_Clock *ui;
    QTime time;
    QString st;

    bell sign;
    bool is_active=true;
};

#endif // ALARM_CLOCK_H
