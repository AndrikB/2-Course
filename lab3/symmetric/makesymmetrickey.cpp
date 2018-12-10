#include "makesymmetrickey.h"
#include "ui_makesymmetrickey.h"
#include <QDebug>

MakeSymmetricKey::MakeSymmetricKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakeSymmetricKey)
{
    ui->setupUi(this);
    this->show();

    connect(ui->size_key_slider, SIGNAL(valueChanged(int)), this, SLOT(changed_size_key_slider()));
    ui->size_key_slider->setValue(32);
    this->setFixedSize(this->size());
}

void MakeSymmetricKey::changed_size_key_slider()
{
    ui->size_key->setText("current size "+QString::number(ui->size_key_slider->value()));
}


MakeSymmetricKey::~MakeSymmetricKey()
{
    this->close();
    delete ui;
    emit close_wndw();
}

void MakeSymmetricKey::on_save_to_clicked()
{
    qDebug()<<1;
    QString s="C:/Users/blagi/OneDrive/Робочий стіл";
    QString name=QFileDialog::getSaveFileName(this,tr("Save File"),s , "*.SymmetricKey");

    QFile fout(name);
    fout.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&fout);

    int size=ui->size_key_slider->value();
    str = new unsigned char [size];
    RAND_bytes(str, size);

    out<<size<<endl;
    for (int i=0;i<size;i++)
    {
        out<<str[i]<<endl;
    }
    fout.close();
    delete [] str;
}

void MakeSymmetricKey::on_exit_clicked()
{
    this->~MakeSymmetricKey();
}
