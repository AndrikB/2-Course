#ifndef DECRYPTSYMMETRIC_H
#define DECRYPTSYMMETRIC_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <openssl/blowfish.h>
#include <gtest/gtest.h>

namespace Ui {
class DecryptSymmetric;
}

class DecryptSymmetric : public QDialog
{
    Q_OBJECT

public:
    explicit DecryptSymmetric(QWidget *parent = nullptr);
    ~DecryptSymmetric();
signals:
    void close_wndw();

public slots:
    void on_old_file_clicked();

    void on_set_key_clicked();

    void on_convert_clicked();

    void on_new_file_clicked();

    void on_WriteKey_clicked();

    void on_exit_clicked();

private:
    Ui::DecryptSymmetric *ui;
    QString new_name;
    QString last_name;
    void rewrite_file(QString s, int n);

    BF_KEY *key= new BF_KEY;
    bool b=false;

    FRIEND_TEST(cryptogragry, encrypt_decrypt);
};

#endif // DECRYPTSYMMETRIC_H
