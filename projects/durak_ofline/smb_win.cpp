#include "smb_win.h"
#include "ui_smb_win.h"

smb_win::smb_win(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::smb_win)
{
    ui->setupUi(this);
}

smb_win::~smb_win()
{
    delete ui;
}

void smb_win::win(bool player)
{
    movie=new QMovie;
    this->show();
    if (player)
    {
        QString way_to_gif;
        QString way_to_music = QDir::currentPath();
        way_to_music=way_to_music.left(way_to_music.lastIndexOf(QChar('/')));
        way_to_music+="/durak_ofline/files";
        way_to_gif=way_to_music;
        way_to_music+="/musik/win.mp3";
        way_to_gif+="/gifs/win.gif";
        sound.setMedia(QUrl(way_to_music));
        sound.play();
        movie->setFileName(way_to_gif);
        qDebug()<<way_to_gif;
        ui->gif->setMovie(movie);
        movie->start();
    }
    else
    {
        QString way_to_gif;
        QString way_to_music = QDir::currentPath();
        way_to_music=way_to_music.left(way_to_music.lastIndexOf(QChar('/')));
        way_to_music+="/durak_ofline/files";
        way_to_gif=way_to_music;
        way_to_music+="/musik/lose.mp3";
        way_to_gif+="/gifs/lose.gif";
        sound.setMedia(QUrl(way_to_music));
        sound.play();
        movie->setFileName(way_to_gif);
        qDebug()<<way_to_gif;
        ui->gif->setMovie(movie);
        movie->start();
    }
}

void smb_win::on_restart_clicked()
{
    delete movie;
    sound.stop();
    emit start();
    this->close();
}
