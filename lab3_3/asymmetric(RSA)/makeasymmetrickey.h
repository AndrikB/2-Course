#ifndef MAKEASYMMERTICKEY_H
#define MAKEASYMMERTICKEY_H

#include <QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

namespace Ui {
class MakeAsymmetricKey;
}

class MakeAsymmetricKey : public QDialog
{
    Q_OBJECT

public:
    explicit MakeAsymmetricKey(QWidget *parent = nullptr);
    ~MakeAsymmetricKey();

private slots:
    void on_save_to_clicked();

private:
    Ui::MakeAsymmetricKey *ui;
};

#endif // MAKEASYMMERTICKEY_H
