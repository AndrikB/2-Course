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

private slots:

    void on_back_clicked();

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
    int step=0;

    int on_1_step_chose=-1;//1 - make key; 2 - encrypt; 3 - decrypt
    void set_encrypt_decrypt();
    void set_registration_authorization();
    void delete_registration_authorization();

    bool is_authorized;
    QVBoxLayout *MainVLayout=new QVBoxLayout;
    QPushButton *free_versionBTN;
    QPushButton *authorizationBTN;
    QPushButton *registrationBTN;
    QPushButton *encryptBTN;
    QPushButton *decryptBTN;
    QPushButton *create_keyBTN;

private slots:
    void registration();
    void authorization();
    void free_version();
    void create_key();
    void encrypt();
    void decrypt();
};

#endif // MAINWINDOW_H
