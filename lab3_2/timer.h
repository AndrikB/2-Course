#ifndef TIMER_H
#define TIMER_H

#include <QDialog>
#include "timer_element.h"
#include <QInputDialog>

namespace Ui {
class Timer;
}

class Timer : public QDialog
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer();

private slots:
    void on_add_new_clicked();
    void write_list();
    void on_make_reverse_clicked();

    void on_pause_continue_button_clicked();

    void on_Delete_clicked();

private:
    Ui::Timer *ui;
    QVector <timer_element*> vec;

};

#endif // TIMER_H
