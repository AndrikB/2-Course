#ifndef BELL_H
#define BELL_H

#include <QDialog>

namespace Ui {
class bell;
}

class bell : public QDialog
{
    Q_OBJECT

public:
    explicit bell(QWidget *parent = nullptr);
    ~bell();

private:
    Ui::bell *ui;
};

#endif // BELL_H
