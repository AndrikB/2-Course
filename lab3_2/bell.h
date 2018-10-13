#ifndef BELL_H
#define BELL_H

#include <QMediaPlayer>
#include <QDialog>
#include <QDir>
#include <QUrl>

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
