#include "makeasymmetrickey.h"
#include "ui_makeasymmertickey.h"

MakeAsymmetricKey::MakeAsymmetricKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakeAsymmetricKey)
{
    ui->setupUi(this);
    this->show();
}

MakeAsymmetricKey::~MakeAsymmetricKey()
{
    delete ui;
}

void MakeAsymmetricKey::on_save_to_clicked()
{
    QString pubKeyWayTo=QFileDialog::getSaveFileName(this,tr("Save File"),"" , "*.PubAsymKey");
    QString PrivKeyWayTo=QFileDialog::getSaveFileName(this,tr("Save File"),"" , "*.PrivAsymKey");
    if (pubKeyWayTo.isNull()||PrivKeyWayTo.isNull())return;

    RSA *rsa = RSA_generate_key(1024, 3, NULL, NULL);
    BIO *bio = BIO_new(BIO_s_mem());
    int size_RSA=RSA_size(rsa);
    //pubKey
    {
        QFile foutPub(pubKeyWayTo);
        foutPub.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream outPub(&foutPub);

        char *pubKey;
        PEM_write_bio_RSAPublicKey(bio, rsa);
        int sizePub = BIO_pending(bio);
        pubKey= new char [sizePub+1];
        BIO_read(bio, pubKey, sizePub);
        outPub<<sizePub<<endl;
        outPub<<size_RSA<<endl;
        for (int i=0;i<sizePub;i++)
        {
             outPub<<pubKey[i];
        }

        delete [] pubKey;
    }

    //privKey
    {
        QFile foutPriv(PrivKeyWayTo);
        foutPriv.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream outPriv(&foutPriv);

        char *privKey;
        PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);//write from rsa to bio
        int sizePriv = BIO_pending(bio);
        privKey= new char [sizePriv+1]; /* Null-terminate */
        BIO_read(bio, privKey, sizePriv);
        outPriv<<sizePriv<<endl;
        outPriv<<size_RSA<<endl;
        for (int i=0;i<sizePriv;i++)
        {
             outPriv<<privKey[i];
        }

        delete [] privKey;
    }



    BIO_free_all(bio);
    RSA_free(rsa);/**/
}
