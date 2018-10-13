#ifndef ALARM_CLOCK_ELEMENT_H
#define ALARM_CLOCK_ELEMENT_H

#include <QDialog>
#include <QDateTime>
#include <QTimer>
#include "bell.h"

namespace Ui {
class alarm_clock_element;
}

class alarm_clock_element : public QDialog
{
    Q_OBJECT

public:
    explicit alarm_clock_element(QWidget *parent = nullptr);
    ~alarm_clock_element();
    QTime time;
    void sett();
    bool is_active=true;
private slots:
    void clock_bell();

private:
    Ui::alarm_clock_element *ui;

    bell *sign;

};

#endif // ALARM_CLOCK_ELEMENT_H
