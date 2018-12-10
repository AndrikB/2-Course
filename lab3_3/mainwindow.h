#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "symmetric/makesymmetrickey.h"
#include "symmetric/encryptsymmetric.h"
#include "symmetric/decryptsymmetric.h"
#include "asymmetric(RSA)/makeasymmetrickey.h"
#include "asymmetric(RSA)/encryptasymmetric.h"
#include "asymmetric(RSA)/decryptasymmetric.h"

#include <openssl/blowfish.h>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    //start step 0
    void on_make_key_clicked();

    //end step 0

    //start step 1
    void on_symmetric_key_clicked();

    //ens step 1

    void step_changet();

    void on_encrypt_clicked();

    void on_decrypt_clicked();

    void on_asymmetric_key_clicked();

    void on_back_clicked();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event)override;

    MakeSymmetricKey *make_symmetric_key=Q_NULLPTR;
    EncryptSymmetric *encrypt_symmetric=Q_NULLPTR;
    DecryptSymmetric *decrypt_symmetric=Q_NULLPTR;
private slots:
    void make_symmetric_key_nullptr();
    void encrypt_symmetric_nullptr();
    void decrypt_symmetric_nullptr();
private:
    MakeAsymmetricKey *make_asymmetric_key;
    EncryptAsymmetric *encrypt_asymmetric;
    DecryptAsymmetric *decrypt_asymmetric;

    int step=0;

    int on_1_step_chose=-1;//1 - make key; 2 - encrypt; 3 - decrypt
};

#endif // MAINWINDOW_H
