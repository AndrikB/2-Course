#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->asymmetric_key->setDisabled(true);
    step_changet();
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Chose file with key"), "", "*.SymmetricKey");
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream FILEin(&fin);
    unsigned char *str=new unsigned char [16];
    qDebug()<<"key";
    for (int i=0;i<16;i++)
    {
        str[i]=(unsigned char)FILEin.readLine().toInt();
        qDebug()<<str[i];
    }
    qDebug()<<"--------------------------";
    BF_KEY *key = new BF_KEY[16];
    BF_set_key(key,16 , str);

    unsigned char *out=new unsigned char[8];
    unsigned char *in=new unsigned char [8];
    qDebug()<<"before all";
    for (int i=0;i<8;i++)
    {
        out[i]=i+'0';
        in[i]=0;
        qDebug()<<out[i];
    }

    BF_ecb_encrypt(out, in, key, BF_ENCRYPT);
    qDebug()<<"after encrypt";
    for (int i=0;i<8;i++)
    {
        out[i]=0;
        qDebug()<<in[i];
    }
    BF_ecb_encrypt(in, out, key, BF_DECRYPT);
    qDebug()<<"after decrypt";
    for (int i=0;i<8;i++)
    {
        qDebug()<<out[i];
    }

}

void MainWindow::step_changet()
{

    ui->asymmetric_key->setVisible(!step);
    ui->symmetric_key->setVisible(!step);
    ui->make_key->setVisible(step);
    ui->encrypt->setVisible(step);
    ui->decrypt->setVisible(step);
    if (step==1)
    {
        ui->back->setText("back");
        ui->info_lbl->setText("Chose action");
    }
    else
    {
        ui->back->setText("exit");
        ui->info_lbl->setText("Chose type of crypto");
    }
}

void MainWindow::on_make_key_clicked()
{
    switch (on_1_step_chose)
    {
    case 1:
        make_symmetric_key= new MakeSymmetricKey;
        connect(make_symmetric_key, SIGNAL(close_wndw()), this, SLOT(make_symmetric_key_nullptr()));
        break;
    case 2:make_asymmetric_key= new MakeAsymmetricKey; break;
    }
}

void MainWindow::make_symmetric_key_nullptr()
{
    make_symmetric_key=Q_NULLPTR;
}

void MainWindow::on_encrypt_clicked()
{
    switch (on_1_step_chose)
    {
    case 1:
        encrypt_symmetric=new EncryptSymmetric;
        connect(encrypt_symmetric, SIGNAL(close_wndw()), this, SLOT(encrypt_symmetric_nullptr()));
        break;
    case 2:encrypt_asymmetric=new EncryptAsymmetric; break;
    }
}

void MainWindow::encrypt_symmetric_nullptr()
{
    encrypt_symmetric=Q_NULLPTR;
}

void MainWindow::on_decrypt_clicked()
{
    switch (on_1_step_chose)
    {
    case 1:
        decrypt_symmetric=new DecryptSymmetric;
        connect(decrypt_symmetric, SIGNAL(close_wndw()), this, SLOT(decrypt_symmetric_nullptr()));
        break;
    case 2:decrypt_asymmetric=new DecryptAsymmetric; break;
    }
}

void MainWindow::decrypt_symmetric_nullptr()
{
    decrypt_symmetric=Q_NULLPTR;
}

void MainWindow::on_symmetric_key_clicked()
{
    on_1_step_chose=1;
    step=1;
    step_changet();
    ui->make_key->setToolTip("generete symetric key for save");
    ui->encrypt->setToolTip("encrypt file using file with key or written key");
    ui->encrypt->setToolTip("decrypt file using file with key or written key");
}



void MainWindow::on_asymmetric_key_clicked()
{
    on_1_step_chose=2;
    step=1;
    step_changet();
    ui->make_key->setToolTip("generete pair keys for save");
    ui->encrypt->setToolTip("encrypt file using file with key ");
    ui->encrypt->setToolTip("decrypt file using file with key ");
}

void MainWindow::on_back_clicked()
{
    if (step==1)
    {
        on_1_step_chose=-1;
        step=0;
        step_changet();
    }
    else
    {
        QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this,"Exit", "Do you really want to leave the WinCrypto?",
                                         QMessageBox::Yes | QMessageBox::No);
           if(reply == QMessageBox::Yes){
               this->close();
           }
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if (this->decrypt_symmetric) this->decrypt_symmetric->close();
    if (this->encrypt_symmetric) this->encrypt_symmetric->close();
    if (this->make_symmetric_key)this->make_symmetric_key->close();
}
