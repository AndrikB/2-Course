#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "symmetric/makesymmetrickey.h"
#include "symmetric/encryptsymmetric.h"
#include "symmetric/decryptsymmetric.h"

#include <openssl/blowfish.h>
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    void closeEvent(QCloseEvent *event)override;
    MakeSymmetricKey *make_symmetric_key=Q_NULLPTR;
    EncryptSymmetric *encrypt_symmetric=Q_NULLPTR;
    DecryptSymmetric *decrypt_symmetric=Q_NULLPTR;

private slots:
    void key_nullptr();
    void encrypt_nullptr();
    void decrypt_nullptr();
private:

    Ui::MainWindow *ui;

    void set_encrypt_decrypt();
    void delete_encrypt_decrypt();
    void set_registration_authorization();
    void delete_registration_authorization();


    bool is_authorized;
    QVBoxLayout *MainVLayout=new QVBoxLayout;

    QPushButton *free_versionBTN;
    QPushButton *authorizationBTN;
    QPushButton *registrationBTN;
    QPushButton *exitBTN;

    QPushButton *encryptBTN;
    QPushButton *decryptBTN;
    QPushButton *create_keyBTN;
    QPushButton *backBTN;

private slots:
    void registration();
    void authorization();
    void free_version();
    void exit();

    void create_key();
    void encrypt();
    void decrypt();
    void back();
};

#endif // MAINWINDOW_H
