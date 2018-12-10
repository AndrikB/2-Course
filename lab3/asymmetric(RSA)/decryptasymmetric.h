#ifndef DECRYPTASYMMETRIC_H
#define DECRYPTASYMMETRIC_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>

#include <openssl/rsa.h>


#include <openssl/pem.h>
namespace Ui {
class DecryptAsymmetric;
}

class DecryptAsymmetric : public QDialog
{
    Q_OBJECT

public:
    explicit DecryptAsymmetric(QWidget *parent = nullptr);
    ~DecryptAsymmetric();

private slots:
    void on_set_key_clicked();

    void on_old_file_clicked();

    void on_new_file_clicked();

    void on_convert_clicked();

private:
    Ui::DecryptAsymmetric *ui;
    QString new_name;
    QString last_name;
    void rewrite_file(QString s, int n);

    RSA *rsa=RSA_new();
    bool b=false;
};

#endif // DECRYPTASYMMETRIC_H
