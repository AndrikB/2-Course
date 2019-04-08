#include "encryptsymmetric.h"
#include "ui_encryptsymmetric.h"

EncryptSymmetric::EncryptSymmetric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncryptSymmetric)
{
    ui->setupUi(this);
    ui->convert->setDisabled(true);
    ui->new_file->setDisabled(true);
    this->setFixedSize(this->size());
}

EncryptSymmetric::~EncryptSymmetric()
{
    this->close();
    delete ui;
    delete key;
    emit close_wndw();
}

void EncryptSymmetric::on_set_key_clicked()
{
    ui->progressCrypt->setValue(0);
    b=false;
    ui->convert->setDisabled(true);
    QString fileName=QFileDialog::getOpenFileName(this, tr("Chose file with key"), "C:/Users/blagi/OneDrive/Робочий стіл", "*.SymmetricKey");
    if (fileName.isEmpty())return;
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream FILEin(&fin);
    int size=FILEin.readLine().toInt();
    unsigned char *str=new unsigned char [size];
    QString st;
    for (int i=0;i<size;i++)
    {
        str[i]=(unsigned char)FILEin.readLine().toInt();
        st+=(unsigned char)str[i];
    }
    ui->label->setText("Password: "+st);
    ui->label->setToolTip(st);
    BF_set_key(key, size, str);
    delete[] str;
    if (!new_name.isEmpty()&&!last_name.isEmpty()) ui->convert->setDisabled(false);
    b=true;
}

void EncryptSymmetric::on_WriteKey_clicked()
{
    b=false;
    ui->convert->setDisabled(true);
    ui->progressCrypt->setValue(0);
    QString st=QInputDialog::getText(this,"password", "Write Password",QLineEdit::Normal);

    ui->label->setText("Password: "+st);
    ui->label->setToolTip(st);

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

void EncryptSymmetric::on_old_file_clicked()
{
    ui->progressCrypt->setValue(0);
    QString s=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл", "*.*");
    if (s.isEmpty())return;
    last_name=s;
    new_name=last_name.left(last_name.lastIndexOf(QChar('.'))+1)+"new_rar";
    ui->new_file->setDisabled(false);

    ui->new_file_label->setText(new_name);
    ui->new_file_label->setAlignment(Qt::AlignRight);
    ui->new_file_label->setToolTip(new_name);

    ui->old_file_label->setText(last_name);
    ui->old_file_label->setAlignment(Qt::AlignRight);
    ui->old_file_label->setToolTip(last_name);

    if (b) ui->convert->setDisabled(false);
}

void EncryptSymmetric::on_new_file_clicked()
{
    new_name=QFileDialog::getSaveFileName(this,tr("Save File"),"C:/Users/blagi/OneDrive/Робочий стіл" , "*.new_rar");
    if (b&&!last_name.isEmpty()) ui->convert->setDisabled(false);
    if (new_name.isEmpty()&&!last_name.isEmpty())new_name=last_name.left(last_name.lastIndexOf(QChar('.'))+1)+"new_rar";
    ui->new_file_label->setText(new_name);
    ui->new_file_label->setAlignment(Qt::AlignRight);
    ui->new_file_label->setToolTip(new_name);
}

void EncryptSymmetric::on_convert_clicked()
{
    //qDebug()<<"start encrypt";
    QFile fin(last_name);
    if (!fin.open(QIODevice::ReadOnly)) return;
    QFile fout(new_name);
    fout.open(QIODevice::WriteOnly);
    char c=last_name.right(last_name.length()-last_name.lastIndexOf(QChar('/'))-1).length();
    fout.putChar(c);
    fout.write(last_name.right(last_name.length()-last_name.lastIndexOf(QChar('/'))-1).toLatin1());
    qint64 sizeFile=fin.size();
    qint64 readyCrypt=0;

    bool not_end_file=true;
    while (not_end_file)
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
                size=i;
                i=8;
            }
            else
            {
                in[i]=*c;
                //qDebug()<<in[i];
            }
            delete c;
        }
        for (int i=size;i<8;i++)
        {
            in[i]=0;
        }


        //qDebug()<<"write out";
        BF_ecb_encrypt(in, out, key, BF_ENCRYPT);

        for (int i=0;i<8;i++)
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
        readyCrypt++;
        ui->progressCrypt->setValue(readyCrypt*8*100/sizeFile);

    }
    fout.close();
    fin.close();
    if (ui->RemoveAfter->checkState())
    {
        QFile::remove(last_name);
    }
    ui->progressCrypt->setValue(100);
    //qDebug()<<"end encrypt";

}

void EncryptSymmetric::on_exit_clicked()
{
    this->~EncryptSymmetric();
}
