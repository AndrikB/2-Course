#include "bell.h"
#include "ui_bell.h"

/**/bool not_disturb=false;



bell::bell(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bell)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    QString name =QDir::currentPath();
    qDebug() <<name;
    while (name[name.size()-1]!='/')
    {
        name.remove(name.size()-1,1);
    }
    qDebug() <<name;
    name=name +"lab3_2/sound/pf.mp3";
    qDebug() <<name;
    //player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("C:/Users/blagi/source/repos/2 course/lab3_2/sound/pf.mp3")));
    player->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators(name)));
    player->setVolume(100);
    player->play();
}

bell::~bell()
{
    player->stop();
    delete ui;
    delete player;

}

void bell::closeEvent(QCloseEvent *event)
{
    this->player->stop();

}
