#ifndef BELL_H
#define BELL_H

#include <QMediaPlayer>
#include <QDialog>
#include <QDir>
#include <QUrl>
#include <QDateTime>
#include <QSound>
extern bool not_disturb;
QTime time_diference(QTime T1, QTime T2);

namespace Ui {
class bell;
}

class bell : public QDialog
{
    Q_OBJECT

public:
    explicit bell(QWidget *parent = nullptr);
    ~bell();
    QMediaPlayer* player;
     void closeEvent(QCloseEvent *event)override;
private:
    Ui::bell *ui;

};

#endif // BELL_H
