#ifndef TIMER_H
#define TIMER_H

#include <QDialog>
#include "timer_element.h"
#include <QInputDialog>

struct list_timer
{
    QVector<int> V;
    QString name;
};

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

    void on_add_new_list_clicked();

    void on_add_del_from_list_clicked();

    void on_delete_list_clicked();

    void on_pause_list_clicked();

private:
    Ui::Timer *ui;
    QVector <timer_element*> vec;
    QVector <list_timer*> list_of_list;
};

#endif // TIMER_H
