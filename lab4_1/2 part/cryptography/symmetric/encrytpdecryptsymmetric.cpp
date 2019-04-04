#include "encrytpdecryptsymmetric.h"
#include "ui_encrytpdecryptsymmetric.h"

EncrytpDecryptSymmetric::EncrytpDecryptSymmetric(int enc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncrytpDecryptSymmetric)
{
    ui->setupUi(this);
    ui->convert->setDisabled(true);
    ui->new_file->setDisabled(true);
    this->setFixedSize(this->size());
    if (enc!=BF_ENCRYPT&&enc!=BF_DECRYPT)exit(11);

    this->enc=enc;
}

EncrytpDecryptSymmetric::~EncrytpDecryptSymmetric()
{
    this->close();
    delete ui;
    delete key;
    emit close_wndw();
}

void EncrytpDecryptSymmetric::set_all_disable()
{
    ui->progressCrypt->setValue(0);
    ui->convert->setDisabled(true);
}

void EncrytpDecryptSymmetric::check_can_convert()
{
    if (key_selected&&!new_filename.isEmpty()&&!old_filename.isEmpty()) ui->convert->setDisabled(false);
}

void EncrytpDecryptSymmetric::on_set_key_clicked()
{
    set_all_disable();
    key_selected=false;

    //chose file with key
    QString fileName=QFileDialog::getOpenFileName(this, tr("Chose file with key"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.SymmetricKey");
    if (fileName.isEmpty())return;
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;

    //read key
    QTextStream FILEin(&fin);
    int size=FILEin.readLine().toInt();
    unsigned char *str=new unsigned char [static_cast<unsigned>(size)];
    QString st;
    for (int i=0;i<size;i++)
    {
        str[i]=static_cast<unsigned char>(FILEin.readLine().toInt());
        st+=static_cast<char>(str[i]);
    }

    //write key
    ui->label->setText("Password: "+st);
    ui->label->setToolTip(st);
    BF_set_key(key, size, str);
    key_selected=true;
    delete[] str;

    check_can_convert();
}

void EncrytpDecryptSymmetric::on_WriteKey_clicked()
{
    set_all_disable();
    key_selected=false;

    //read key
    QString st=QInputDialog::getText(this,"password", "Write Password",QLineEdit::Normal);
    if (st.isEmpty())return;

    //convert key
    int size=st.length();
    unsigned char *str=new unsigned char [static_cast<unsigned>(size)];
    for (int i=0;i<size;i++)
        str[i]=static_cast<unsigned char>(st[i].toLatin1());

    //write key
    ui->label->setText("Password: "+st);
    ui->label->setToolTip(st);
    BF_set_key(key, size, str);
    key_selected=true;
    delete[] str;

    check_can_convert();
}

void EncrytpDecryptSymmetric::set_filename_to_fileLBL(QString filename, QLabel *fileLBL)
{
    fileLBL->setText(filename);
    fileLBL->setToolTip(filename);
}

void EncrytpDecryptSymmetric::remove_last_n_char(QString filename, int n)
{
    QFile fin(filename);
    fin.open(QIODevice::ReadOnly);
    QFile fout(filename.left(filename.lastIndexOf(QChar('/'))+1)+"tmp.tmp");
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
    QFile::remove(filename);
    QFile::rename(filename.left(filename.lastIndexOf(QChar('/'))+1)+"tmp.tmp", filename);
    delete c;
}

void EncrytpDecryptSymmetric::on_old_file_clicked()
{
    //chose file
    QString s;
    if (enc==BF_ENCRYPT)
        s=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.*");
    else
        s=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.new_rar");
    if (s.isEmpty())return;
    QFile fin(s);
    if (!fin.open(QIODevice::ReadWrite)) return;
    old_filename=s;
    ui->new_file->setDisabled(false);

    //auto generation new filename
    if (enc==BF_ENCRYPT)
    {
        new_filename=old_filename.left(old_filename.lastIndexOf(QChar('.'))+1)+"new_rar";
    }
    else
    {
        char *c=new char;
        fin.getChar(c);
        new_filename=fin.read(static_cast<int>(*c));
        new_filename=old_filename.left(old_filename.lastIndexOf(QChar('.'))+1)+new_filename;
        delete c;
    }

    fin.close();

    set_filename_to_fileLBL(new_filename, ui->new_file_label);
    set_filename_to_fileLBL(old_filename, ui->old_file_label);
    set_all_disable();
    check_can_convert();
}

void EncrytpDecryptSymmetric::on_new_file_clicked()
{
    QString s;
    //chose file
    if (enc==BF_ENCRYPT)
    {
        s=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.new_rar");
    }
    else
    {
        s=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.*");
    }
    if (!s.isEmpty()) new_filename=s;

    set_filename_to_fileLBL(new_filename, ui->new_file_label);

    set_all_disable();
    check_can_convert();
}

void EncrytpDecryptSymmetric::on_convert_clicked()
{
    qDebug()<<"start encrypt ";
    QTime start=QTime::currentTime();
    QFile fin(old_filename);
    if (!fin.open(QIODevice::ReadOnly)) return;
    QFile fout(new_filename);
    fout.open(QIODevice::WriteOnly);

    if (enc==BF_ENCRYPT) //add name
    {
        QString name_file=old_filename.right(old_filename.length()-old_filename.lastIndexOf(QChar('.'))-1);
        char c=static_cast<char>(name_file.length());
        fout.putChar(c);
        fout.write(name_file.toLatin1());
    }
    else //skip name
    {
        char *c=new char;
        fin.getChar(c);
        QString z;
        z=fin.read(static_cast<int>(*c));
        delete c;
    }

    qDebug()<<"end name";
    qint64 sizeFile=fin.size();
    qint64 readyCrypt=0;

    bool not_end_file=true;
    unsigned char *in=new unsigned char[8], *out=new unsigned char[8];
    while (not_end_file)
    {
        int size=8;

        for (int i=0;i<8;i++)
        {
            char *c=new char;
            if (!fin.getChar(c))
            {
                if (enc==BF_ENCRYPT)
                {
                    size=i;
                    i=8;
                }
                else
                {
                    *c=static_cast<char>(in[0]);
                    fout.close();
                    fin.close();

                    remove_last_n_char(new_filename, *c);
                    if (ui->RemoveAfter->checkState())
                    {
                        QFile::remove(old_filename);
                    }
                    ui->progressCrypt->setValue(100);
                    delete[] in;
                    delete[] out;
                    delete c;
                    qDebug()<<"end decrypt"<<start.msecsTo(QTime::currentTime())<<"msec";
                    return;
                }

            }
            else
            {
                in[i]=static_cast<unsigned char>(*c);
            }
            delete c;
        }
        for (int i=size;i<8;i++)
        {
            in[i]=0;
        }

        BF_ecb_encrypt(in, out, key, enc);

        for (int i=0;i<8;i++)
        {
            fout.putChar(static_cast<char>(out[i]));
        }
        if (size!=8)
        {
            not_end_file=false;
            fout.putChar(static_cast<char>(8-size));
        }

        readyCrypt++;
        ui->progressCrypt->setValue(static_cast<int>(readyCrypt*8*100/sizeFile));

    }
    delete[] in;
    delete[] out;
    fout.close();
    fin.close();
    if (ui->RemoveAfter->checkState())
    {
        QFile::remove(old_filename);
    }
    ui->progressCrypt->setValue(100);
    qDebug()<<"end encrypt "<<start.msecsTo(QTime::currentTime())<<"msec";

}

void EncrytpDecryptSymmetric::on_exit_clicked()
{
    this->~EncrytpDecryptSymmetric();
}


