#ifndef TIMER_ELEMENT_H
#define TIMER_ELEMENT_H

#include <QDialog>
#include<QTimer>
#include<QDateTime>
#include "bell.h"

namespace Ui {
class timer_element;
}

class timer_element : public QDialog
{
    Q_OBJECT

public:
    explicit timer_element(QWidget *parent = nullptr);
    ~timer_element();
    QTimer *timer;
    /**/QTime time;
    /**/QTime tmp;//if is pause
    void sett();
    /**/bool is_active=true;
    /**/bool is_not_pause=true;
private slots:
    void clock_bell();
private:
    Ui::timer_element *ui;
    bell *sign;
};

#endif // TIMER_ELEMENT_H
