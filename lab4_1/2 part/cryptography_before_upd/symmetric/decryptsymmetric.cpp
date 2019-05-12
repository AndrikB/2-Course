#include "decryptsymmetric.h"
#include "ui_decryptsymmetric.h"
#include <QElapsedTimer>

DecryptSymmetric::DecryptSymmetric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecryptSymmetric)
{
    ui->setupUi(this);
    ui->new_file->setDisabled(true);
    ui->convert->setDisabled(true);
    this->setFixedSize(this->size());
}

DecryptSymmetric::~DecryptSymmetric()
{
    this->close();
    delete ui;
    delete key;
    emit close_wndw();
}

void DecryptSymmetric::on_set_key_clicked()
{
    b=false;
    ui->convert->setDisabled(true);
    ui->progressCrypt->setValue(0);
    QString fileName=QFileDialog::getOpenFileName(this, tr("Chose file with key"), "C:/Users/blagi/OneDrive/Робочий стіл", "*.SymmetricKey");
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream FILEin(&fin);
    int size=FILEin.readLine().toInt();
    unsigned char *str=new unsigned char [size];
    QString st;
    for (int i=0;i<size;i++)
    {
        str[i]=(unsigned char)FILEin.readLine().toInt();
        st+=str[i];
    }
    ui->key_lbl->setText("Password: "+st);
    BF_set_key(key,size , str);
    delete [] str;
    if (!new_name.isEmpty()&&!last_name.isEmpty()) ui->convert->setDisabled(false);
    b=true;
}

void DecryptSymmetric::on_WriteKey_clicked()
{
    b=false;
    ui->convert->setDisabled(true);
    ui->progressCrypt->setValue(0);
    QString st=QInputDialog::getText(this,"password", "Write Password");
    if (st.isEmpty())return;
    int size=st.length();
    unsigned char *str=new unsigned char [size];
    for (int i=0;i<size;i++)
        str[i]=st[i].toLatin1();

    BF_set_key(key, size, str);
    delete[] str;
    if (!new_name.isEmpty()&&!last_name.isEmpty()) ui->convert->setDisabled(false);
    b=true;
}

void DecryptSymmetric::rewrite_file(QString f1, int n)
{
    QFile fin(f1);
    fin.open(QIODevice::ReadOnly);
    QFile fout(f1.left(f1.lastIndexOf(QChar('/'))+1)+"tmp.tmp");
    fout.open(QIODevice::WriteOnly);
    char *c=new char;
    qint64  size=0, originalSize;
    originalSize=fin.size();
    size=originalSize-n;

    while (size>0)
    {
        ui->progressCrypt->setValue(50+size/originalSize*50);

        fin.getChar(c);
        fout.putChar(*c);
        size--;
    }

    fin.close();
    fout.close();
    QFile::remove(f1);
    QFile::rename(f1.left(f1.lastIndexOf(QChar('/'))+1)+"tmp.tmp", f1);
    delete c;
}

void DecryptSymmetric::on_old_file_clicked()
{
    ui->progressCrypt->setValue(0);
    ui->new_file->setDisabled(false);
    last_name=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл", "*.new_rar");
    QFile fin(last_name);
    if (!fin.open(QIODevice::ReadWrite)) return;
    char *c=new char;
    fin.getChar(c);
    new_name=fin.read((int)*c);
    new_name=last_name.left(last_name.lastIndexOf(QChar('/'))+1)+new_name;
    fin.close();
    ui->old_file_label->setText(last_name);
    ui->new_file_label->setText(new_name);
    if (b)ui->convert->setDisabled(false);
}

void DecryptSymmetric::on_new_file_clicked()
{
    ui->progressCrypt->setValue(0);
    QString s=QFileDialog::getSaveFileName(this,tr("Save File"),"C:/Users/blagi/OneDrive/Робочий стіл" , "*.*");
    if (!s.isEmpty()) new_name=s;
    if (b&&!last_name.isEmpty()) ui->convert->setDisabled(false);
    ui->new_file_label->setText(new_name);
}

void DecryptSymmetric::on_convert_clicked()
{
    qDebug()<<"start decrypt";
    QElapsedTimer t;
    t.start();
    QFile fin(last_name);
    if (!fin.open(QIODevice::ReadOnly)) return;
    QFile fout(new_name);
    fout.open(QIODevice::WriteOnly);
    //skip name
    {
        char *c=new char;
        fin.getChar(c);
        QString z;
        z=fin.read((int)*c);
        delete c;
    }

    qint64 sizeFile=fin.size();
    qint64 readyCrypt=0;
    while (1)
    {
        //qDebug()<<"------------------------------------";
        unsigned char *in=new unsigned char[8], *out=new unsigned char[8];
        int size=8;
        //qDebug()<<"write in";
        for (int i=0;i<8;i++)
        {
            char *c=new char;
            if (!fin.getChar(c))
            {
                //del symbol end return out
                *c=in[0];
                fout.close();
                fin.close();
                //qDebug()<<"end decrypt";
                rewrite_file(new_name, *c);
                if (ui->remove_after_chkbx->checkState())
                {
                    QFile::remove(last_name);
                }
                ui->progressCrypt->setValue(100);
                delete[] in;
                delete[] out;
                delete c;
                qDebug()<<t.elapsed();
                qDebug()<<"end encrypt";
                return;

            }
            else
            {
                in[i]=*c;
                //qDebug()<<in[i];
            }
            delete c;
        }

        BF_ecb_encrypt(in, out, key, BF_DECRYPT);

        //qDebug()<<"write out";
        for (int i=0;i<size;i++)
        {
            //qDebug()<<out[i];
            fout.putChar(out[i]);
        }
        delete[] in;
        delete[] out;
        readyCrypt++;
        ui->progressCrypt->setValue(readyCrypt*8*50/sizeFile);
    }
}


void DecryptSymmetric::on_exit_clicked()
{
    this->~DecryptSymmetric();
}
