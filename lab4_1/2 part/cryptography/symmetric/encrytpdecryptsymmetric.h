#ifndef ENCRYTPDECRYPTSYMMETRIC_H
#define ENCRYTPDECRYPTSYMMETRIC_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>
#include <openssl/blowfish.h>
#include <QLabel>
#include <QTime>
#include <QClipboard>

#include <gtest/gtest.h>

namespace Ui {
class EncrytpDecryptSymmetric;
}

class EncrytpDecryptSymmetric : public QDialog
{
    Q_OBJECT

public:
    explicit EncrytpDecryptSymmetric(int enc, bool is_authorizated, QWidget *parent = nullptr);
    ~EncrytpDecryptSymmetric();


private slots:
    void on_old_file_clicked();
    void on_new_file_clicked();
    void on_set_key_clicked();
    void on_WriteKey_clicked();

    void on_text_radiobtn_clicked();
    void on_file_radiobtn_clicked();

    void on_convert_clicked();

    void on_exit_clicked();



signals:
    void close_wndw();
private:
    Ui::EncrytpDecryptSymmetric *ui;
    int enc;
    bool is_authorizated;
    QString new_filename;
    QString old_filename;

    BF_KEY *key= new BF_KEY;
    bool key_selected=false;//todo rename

    void set_all_disable();
    void check_can_convert();
    void clear_all();
    void set_not_authorizated();

    void set_key(QString key, int size);
    void set_filename_to_fileLBL(QString filename, QLabel *fileLBL);
    void set_old_and_new_filename(QString s);

    void encrypt_decrypt_file();

    void closeEvent(QCloseEvent *event)override;
    FRIEND_TEST(cryptogragry, encrypt_decrypt);
};

#endif // ENCRYTPDECRYPTSYMMETRIC_H
