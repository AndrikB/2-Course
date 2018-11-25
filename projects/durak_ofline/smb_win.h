#ifndef SMB_WIN_H
#define SMB_WIN_H

#include <QDialog>
#include <QMediaPlayer>
#include <QDir>
#include <QDebug>
#include <QMovie>
namespace Ui {
class smb_win;
}

class smb_win : public QDialog
{
    Q_OBJECT

public:
    explicit smb_win(QWidget *parent = nullptr);
    ~smb_win();
    Ui::smb_win *ui;
    void win(bool player);
signals:
    void start();

private slots:
    void on_restart_clicked();

private:
    QMediaPlayer sound;
    QMovie *movie;


};

#endif // SMB_WIN_H
