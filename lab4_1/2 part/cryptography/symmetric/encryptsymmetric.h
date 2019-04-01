#ifndef ENCRYPTSYMMETRIC_H
#define ENCRYPTSYMMETRIC_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <openssl/blowfish.h>

namespace Ui {
class EncryptSymmetric;
}

class EncryptSymmetric : public QDialog
{
    Q_OBJECT

public:
    explicit EncryptSymmetric(QWidget *parent = nullptr);
    ~EncryptSymmetric();

private slots:
    void on_old_file_clicked();

    void on_convert_clicked();

    void on_new_file_clicked();

    void on_set_key_clicked();

    void on_WriteKey_clicked();

    void on_exit_clicked();
signals:
    void close_wndw();
private:
    Ui::EncryptSymmetric *ui;
    QString new_name;
    QString last_name;

    BF_KEY *key= new BF_KEY;
    bool b=false;
};

#endif // ENCRYPTSYMMETRIC_H
