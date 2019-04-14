#include "encrytpdecryptsymmetric.h"
#include "ui_encrytpdecryptsymmetric.h"

EncrytpDecryptSymmetric::EncrytpDecryptSymmetric(int enc, bool is_authorizated, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncrytpDecryptSymmetric)
{
    ui->setupUi(this);
    ui->convert->setDisabled(true);
    ui->new_file->setDisabled(true);
    this->setFixedSize(this->size());
    if (enc==BF_ENCRYPT) {
        ui->convert->setText("Encrytp");
        this->setWindowTitle("Encrypt");
    }
    else if (enc==BF_DECRYPT) {
        ui->convert->setText("Decrypt");
        this->setWindowTitle("Decrypt");
    }
    else exit(11);

    on_text_radiobtn_clicked();
    this->enc=enc;
    this->is_authorizated=is_authorizated;
    if (!is_authorizated) set_not_authorizated();

}

EncrytpDecryptSymmetric::~EncrytpDecryptSymmetric()
{
    this->close();
    delete ui;
    delete key;
    emit close_wndw();
}

void EncrytpDecryptSymmetric::set_not_authorizated()
{
    ui->file_radiobtn->setDisabled(true);
    ui->file_radiobtn->setToolTip("You are not authorizated");
    ui->new_file->setToolTip("You are not authorizated");
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

void EncrytpDecryptSymmetric::set_key(QString key, int size)
{
    unsigned char *str=new unsigned char [static_cast<unsigned>(size)];
    for (int i=0;i<size;i++)
        str[i]=static_cast<unsigned char>(key[i].toLatin1());

    ui->password_label->setText("Password: "+key);
    ui->password_label->setToolTip(key);
    BF_set_key(this->key, size, str);
    key_selected=true;
    delete[] str;
    check_can_convert();
}

void EncrytpDecryptSymmetric::on_set_key_clicked()
{
    set_all_disable();
    ui->password_label->setText("Password: ");
    key_selected=false;

    //chose file with key
    QString fileName=QFileDialog::getOpenFileName(this, tr("Chose file with key"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.SymmetricKey");
    if (fileName.isEmpty())return;
    QFile fin(fileName);
    if (!fin.open(QIODevice::ReadOnly|QIODevice::Text)) return;

    //read key
    QTextStream FILEin(&fin);
    int size=FILEin.readLine().toInt();
    QString key;
    for (int i=0;i<size;i++)
    {
        key+=static_cast<char>(FILEin.readLine().toInt());
    }
    set_key(key, size);

}

void EncrytpDecryptSymmetric::on_WriteKey_clicked()
{
    set_all_disable();
    ui->password_label->setText("Password: ");
    key_selected=false;

    //read key
    QString key=QInputDialog::getText(this,"password", "Write Password",QLineEdit::Normal);
    if (key.isEmpty())return;

    int size=key.length();
    set_key(key, size);

}

void EncrytpDecryptSymmetric::set_filename_to_fileLBL(QString filename, QLabel *fileLBL)
{
    fileLBL->setText(filename);
    fileLBL->setToolTip(filename);
}

void EncrytpDecryptSymmetric::set_old_and_new_filename(QString s)
{
    //chose file

    QFile fin(s);
    if (!fin.open(QIODevice::ReadWrite)) return;
    old_filename=s;


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


}

void EncrytpDecryptSymmetric::on_old_file_clicked()
{
    if (ui->text_radiobtn->isChecked())//text
    {
        QString text=QInputDialog::getText(this,"Text", "Write text to crypt",QLineEdit::Normal);
        if (text.size()==0) return;
        QString s;
        if (enc==BF_ENCRYPT)
            s="tmp.tmp";
        else
            s="tmp.new_rar";

        QFile f1(s);
        f1.open(QIODevice::WriteOnly);
        QTextStream out(&f1);
        out<<text;
        f1.close();
        set_filename_to_fileLBL(text, ui->old_file_label);
        set_old_and_new_filename(s);
    }
    else {//file
        QString s;
        if (enc==BF_ENCRYPT)
            s=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.*");
        else
            s=QFileDialog::getOpenFileName(this, tr("File to crypt"), "C:/Users/blagi/OneDrive/Робочий стіл/lab4.1.2 test", "*.new_rar");
        if (s.isEmpty())return;
        set_old_and_new_filename(s);

        ui->new_file->setDisabled(false);
        set_filename_to_fileLBL(new_filename, ui->new_file_label);
        set_filename_to_fileLBL(old_filename, ui->old_file_label);
    }

    set_all_disable();
    check_can_convert();
}

void EncrytpDecryptSymmetric::on_new_file_clicked()
{
    if (ui->text_radiobtn->isChecked())//text
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(ui->new_file_label->text());

    }
    else {//file
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

}

void EncrytpDecryptSymmetric::encrypt_decrypt_file()
{
    QFile fin(old_filename);
    if (!fin.open(QIODevice::ReadOnly)) return;
    QFile fout(new_filename);
    fout.open(QIODevice::WriteOnly);

    /*name*/{
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
    }
    qint64 sizeFile=fin.size();
    qint64 readyCrypt=0;

    bool not_end_file=true;
    unsigned char *in=new unsigned char[8], *out=new unsigned char[8];
    unsigned char *z =new unsigned char[2];
    char *c=new char;
    if (enc==BF_DECRYPT)//read first 2 bytes
    {
        fin.getChar(c);
        z[0]=static_cast<unsigned char>(*c);
        fin.getChar(c);
        z[1]=static_cast<unsigned char>(*c);
    }
    int size=8;
    int count_zeros_if_end_file=0;
    int count_real_bytes;
    while (not_end_file)
    {

        for (int i=0;i<8;i++)//read 8 sybmols
        {
            if (enc==BF_DECRYPT)
            {
                if (i==0)
                {
                    in[0]=z[0];
                    in[1]=z[1];
                    i=2;
                }
            }

            if (!fin.getChar(c))
            {
                if (enc==BF_ENCRYPT)
                {
                    not_end_file=false;
                    size=i;
                    i=8;
                }
                else//file was changed. cant decrypt file;
                {

                    exit(12);
                }

            }
            else
            {
                in[i]=static_cast<unsigned char>(*c);
            }
            if (enc==BF_DECRYPT)
            {
                if (i==7)
                {
                    fin.getChar(c);
                    z[0]=static_cast<unsigned char>(*c);
                    if (!fin.getChar(c))
                    {
                        not_end_file=false;
                        count_zeros_if_end_file=z[0];
                        //end file

                    }
                    else
                    {
                        z[1]=static_cast<unsigned char>(*c);
                    }
                }
            }

        }
        for (int i=size;i<8;i++)
        {
            in[i]=0;
        }

        BF_ecb_encrypt(in, out, key, enc);

        count_real_bytes=8-count_zeros_if_end_file;
        for (int i=0;i<count_real_bytes;i++)
        {
            fout.putChar(static_cast<char>(out[i]));
        }
        if (size!=8)
        {
            fout.putChar(static_cast<char>(8-size));
        }
        readyCrypt++;
        if (sizeFile==0)ui->progressCrypt->setValue(100);
            else ui->progressCrypt->setValue(static_cast<int>(readyCrypt*8*100/sizeFile));

    }
    delete[] in;
    delete[] out;
    delete c;
    fout.close();
    fin.close();
    if (ui->RemoveAfter->checkState()||ui->text_radiobtn->isChecked())
    {
        QFile::remove(old_filename);
    }
    ui->progressCrypt->setValue(100);
    if (is_authorizated)ui->new_file->setDisabled(false);
}


void EncrytpDecryptSymmetric::on_convert_clicked()
{
    if (ui->text_radiobtn->isChecked())//text
    {
         encrypt_decrypt_file();
         QFile f1(new_filename);
         f1.open(QIODevice::ReadOnly);
         QString new_text;
         QTextStream in(&f1);
         new_text=in.read(f1.size());
         f1.close();

         set_filename_to_fileLBL(new_text, ui->new_file_label);
    }
    else {//file
        encrypt_decrypt_file();
    }
}

void EncrytpDecryptSymmetric::on_exit_clicked()
{
    this->~EncrytpDecryptSymmetric();
}


void EncrytpDecryptSymmetric::collapse_all()
{
    old_filename="";
    new_filename="";
    set_filename_to_fileLBL(new_filename, ui->new_file_label);
    set_filename_to_fileLBL(old_filename, ui->old_file_label);
    set_all_disable();
}

void EncrytpDecryptSymmetric::on_text_radiobtn_clicked()
{
    collapse_all();

    ui->RemoveAfter->setVisible(false);
    ui->old_file->setText("set text");
    ui->new_file->setText("copy");
}

void EncrytpDecryptSymmetric::on_file_radiobtn_clicked()
{
    collapse_all();

    ui->RemoveAfter->setVisible(true);
    ui->old_file->setText("old file");
    ui->new_file->setText("new file");
}
