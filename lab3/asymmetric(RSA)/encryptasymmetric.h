#ifndef ENCRYPTASYMMETRIC_H
#define ENCRYPTASYMMETRIC_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>

#include <openssl/rsa.h>


#include <openssl/pem.h>
namespace Ui {
class encryptAsymmetric;
}

class EncryptAsymmetric : public QDialog
{
    Q_OBJECT

public:
    explicit EncryptAsymmetric(QWidget *parent = nullptr);
    ~EncryptAsymmetric();

private slots:
    void on_set_key_clicked();

    void on_old_file_clicked();

    void on_new_file_clicked();

    void on_convert_clicked();

private:
    Ui::encryptAsymmetric *ui;
    QString new_name;
    QString last_name;

    RSA *rsa=RSA_new();
    bool b=false;
    int _RSA_size=0;
};

#endif // ENCRYPTASYMMETRIC_H
