#include "encryptasymmetric.h"
#include "ui_encryptasymmetric.h"

 #include <openssl/bn.h>

EncryptAsymmetric::EncryptAsymmetric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::encryptAsymmetric)
{
    ui->setupUi(this);
    this->show();
}

EncryptAsymmetric::~EncryptAsymmetric()
{
    delete ui;
    RSA_free(rsa);
}

void EncryptAsymmetric::on_set_key_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Chose file with key"), "", "*.PubAsymKey *en.PrivAsymKey");
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream FILEin(&fin);

    int size=FILEin.readLine().toInt();
    _RSA_size=FILEin.readLine().toInt();
    //qDebug()<<size;
    char *str=new char [size];
    for (int i=0;i<size;i++)
    {
        QString s=FILEin.read(1);
        str[i]=s.toLatin1()[0];
    }

    qDebug()<<QString::fromLatin1(str);
    BIO *bio = BIO_new(BIO_s_mem());
    BIO_write(bio, str, size);
    RSA* t = RSA_new();
    rsa=PEM_read_bio_RSAPublicKey(bio, &t, NULL, NULL);

    RSA_free(t);
    BIO_free_all(bio);
    delete [] str;
}

void EncryptAsymmetric::on_old_file_clicked()
{
    QString s=QFileDialog::getOpenFileName(this, tr("File to crypt"), last_name, "*.*");
    if (s.isEmpty())return;
    last_name=s;
    new_name=last_name.left(last_name.lastIndexOf(QChar('.'))+1)+"RSA_rar";
    //if (b) ui->convert->setDisabled(false);
}



void EncryptAsymmetric::on_new_file_clicked()
{

}

void EncryptAsymmetric::on_convert_clicked()
{
    qDebug()<<"start encrypt";
    QFile fin(last_name);
    if (!fin.open(QIODevice::ReadOnly)) return;
    QFile fout(new_name);
    fout.open(QIODevice::WriteOnly);
    char c=last_name.right(last_name.length()-last_name.lastIndexOf(QChar('/'))-1).length();
    fout.putChar(c);
    fout.write(last_name.right(last_name.length()-last_name.lastIndexOf(QChar('/'))-1).toLatin1());
    int rsa_size=RSA_size(rsa);
    qDebug()<<rsa_size<<_RSA_size;
    bool not_end_file=true;
    while (not_end_file)
    {
        qDebug()<<"------------------------------------";

        unsigned char *in=new unsigned char[8], *out=new unsigned char[_RSA_size];
        int size=8;
        qDebug()<<"write in";
        for (int i=0;i<8;i++)
        {
            char *c=new char;
            if (!fin.getChar(c))
            {
                size=i;
                i=8;
            }
            else
            {
                in[i]=*c;
                qDebug()<<in[i];
            }
            delete c;
        }
        for (int i=size;i<8;i++)
        {
            in[i]=0;
        }
        qDebug()<<"before";
        qDebug()<<RSA_public_encrypt(8, in, out, rsa, RSA_PKCS1_OAEP_PADDING);
        qDebug()<<"after";
        for (int i=0;i<_RSA_size;i++)
        {
            //qDebug()<<(char)out[i]<<out[i];
            fout.putChar(out[i]);
        }
        if (size!=8)
        {
            not_end_file=false;
            fout.putChar(8-size);
        }
        delete[] in;
        delete[] out;



    }


    qDebug()<<"end encrypt";
}




