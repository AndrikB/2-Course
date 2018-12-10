#include "decryptasymmetric.h"
#include "ui_decryptasymmetric.h"

DecryptAsymmetric::DecryptAsymmetric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecryptAsymmetric)
{
    ui->setupUi(this);
}

DecryptAsymmetric::~DecryptAsymmetric()
{
    delete ui;
    RSA_free(rsa);
}

void DecryptAsymmetric::on_set_key_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Chose file with key"), "", "*en.PubAsymKey *.PrivAsymKey");
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream FILEin(&fin);

    int size=FILEin.readLine().toInt();
    //qDebug()<<size;
    char *str=new char [size];
    for (int i=0;i<size;i++)
    {
        QString s=FILEin.read(1);
        str[i]=s.toLatin1()[0];
    }

    //qDebug()<<QString::fromLatin1(str);
    BIO *bio = BIO_new(BIO_s_mem());
    BIO_write(bio, str, size);
    RSA* t = RSA_new();
    rsa=PEM_read_bio_RSAPrivateKey(bio, &t, NULL, NULL);

    RSA_free(t);
    BIO_free_all(bio);
    delete [] str;
}

void DecryptAsymmetric::rewrite_file(QString f1, int n)
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
        //ui->progressCrypt->setValue(50+size/originalSize*50);

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


void DecryptAsymmetric::on_old_file_clicked()
{
    QString s=QFileDialog::getOpenFileName(this, tr("File to crypt"), last_name, "*.RSA_rar");
    if (s.isEmpty())return;
    last_name=s;
    QFile fin(last_name);
    if (!fin.open(QIODevice::ReadWrite)) return;
    char *c=new char;
    fin.getChar(c);
    new_name=fin.read((int)*c);
    new_name=last_name.left(last_name.lastIndexOf(QChar('/'))+1)+new_name;
    fin.close();
    //ui->old_file_label->setText(last_name);
    //ui->new_file_label->setText(new_name);
    //if (b) ui->convert->setDisabled(false);
}

void DecryptAsymmetric::on_new_file_clicked()
{

}

void DecryptAsymmetric::on_convert_clicked()
{
    qDebug()<<"start decrypt";
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

    char c;
    fin.getChar(&c);
    int size_RSA=fin.read(c).toInt();

    while (1)
    {
        //qDebug()<<"------------------------------------";
        unsigned char *in=new unsigned char[size_RSA], *out=new unsigned char[8];
        int size=8;
        //qDebug()<<"write in";
        for (int i=0;i<size_RSA;i++)
        {
            char *c=new char;
            if (!fin.getChar(c))
            {
                //del symbol end return out
                *c=in[0];
                fout.close();
                fin.close();
                qDebug()<<"end decrypt";
                //rewrite_file(new_name, *c);
                delete[] in;
                delete[] out;
                delete c;
                return;

            }
            else
            {
                in[i]=*c;
                //qDebug()<<in[i];
            }
            delete c;
        }

        qDebug()<<RSA_private_decrypt(size_RSA, in, out,rsa, RSA_PKCS1_OAEP_PADDING);

        //qDebug()<<"write out";
        for (int i=0;i<size;i++)
        {
            //qDebug()<<out[i];
            fout.putChar(out[i]);
        }
        delete[] in;
        delete[] out;
        //readyCrypt++;
        //ui->progressCrypt->setValue(readyCrypt*8*50/sizeFile);
    }


}


