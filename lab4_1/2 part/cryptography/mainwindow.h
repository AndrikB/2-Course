#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "symmetric/makesymmetrickey.h"
#include "symmetric/encrytpdecryptsymmetric.h"

#include <openssl/blowfish.h>
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:

    void closeEvent(QCloseEvent *event)override;
    MakeSymmetricKey *make_symmetric_key=Q_NULLPTR;
    EncrytpDecryptSymmetric *encrypt_symmetric=Q_NULLPTR;
    EncrytpDecryptSymmetric *decrypt_symmetric=Q_NULLPTR;

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
    void close_subwindows();


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
    void end_authorization();
    void free_version();
    void exit();

    void create_key();
    void encrypt();
    void decrypt();
    void back();
};

#endif // MAINWINDOW_H
