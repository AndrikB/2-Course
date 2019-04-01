#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *w=new QWidget;
    w->setLayout(MainVLayout);
    setCentralWidget(w);

    set_registration_authorization();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::set_registration_authorization()
{
    //registration
    {
        registrationBTN=new QPushButton("registration");
        connect(registrationBTN, SIGNAL(clicked()), this, SLOT(registration()));
        MainVLayout->addWidget(registrationBTN);
    }

    //authorization
    {
        authorizationBTN=new QPushButton("authorization");
        connect(authorizationBTN, SIGNAL(clicked()), this, SLOT(authorization()));
        MainVLayout->addWidget(authorizationBTN);
    }

    //free version
    {
        free_versionBTN=new QPushButton("free version");
        connect(free_versionBTN, SIGNAL(clicked()), this, SLOT(free_version()));
        MainVLayout->addWidget(free_versionBTN);
    }

    //exit
    {
        exitBTN=new QPushButton("exit");
        connect(exitBTN, SIGNAL(clicked()), this, SLOT(exit()));
        MainVLayout->addWidget(exitBTN);

    }

}

void MainWindow::delete_registration_authorization()
{
    delete registrationBTN;
    delete authorizationBTN;
    delete free_versionBTN;
    delete exitBTN;
}

void MainWindow::registration()
{

}

void MainWindow::authorization()
{

}

void MainWindow::free_version()
{
    delete_registration_authorization();
    is_authorized=false;
    set_encrypt_decrypt();
}

void MainWindow::exit()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Exit", "Do you really want to leave the WinCrypto?",
                                     QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
           this->close();
    }
}

void MainWindow::set_encrypt_decrypt()
{
    {//encrypt
        encryptBTN=new QPushButton("encrypt");
        connect(encryptBTN, SIGNAL(clicked()), this, SLOT(encrypt()));
        encryptBTN->setToolTip("encrypt file using file with key or written key");
        MainVLayout->addWidget(encryptBTN);
    }

    {//decrypt
        decryptBTN=new QPushButton("decrypt");
        connect(decryptBTN, SIGNAL(clicked()), this, SLOT(decrypt()));
        decryptBTN->setToolTip("decrypt file using file with key or written key");
        MainVLayout->addWidget(decryptBTN);
    }

    {//key
        create_keyBTN=new QPushButton("create key");
        connect(create_keyBTN, SIGNAL(clicked()), this, SLOT(create_key()));
        create_keyBTN->setToolTip("generete symetric key for save");
        MainVLayout->addWidget(create_keyBTN);
    }

    //back
    {
       backBTN=new QPushButton();
       connect(backBTN, SIGNAL(clicked()), this, SLOT(back()));
       if (is_authorized) {
           backBTN->setText("log out");
       }
       else {
           backBTN->setText("back");
       }
       MainVLayout->addWidget(backBTN);
    }
}

void MainWindow::delete_encrypt_decrypt()
{
    delete backBTN;
    delete create_keyBTN;
    delete encryptBTN;
    delete decryptBTN;
}

void MainWindow::create_key()
{

    make_symmetric_key= new MakeSymmetricKey;
    connect(make_symmetric_key, SIGNAL(close_wndw()), this, SLOT(key_nullptr()));
}

void MainWindow::key_nullptr()
{
    make_symmetric_key=Q_NULLPTR;
}

void MainWindow::encrypt()
{
    encrypt_symmetric=new EncryptSymmetric;
    connect(encrypt_symmetric, SIGNAL(close_wndw()), this, SLOT(encrypt_nullptr()));
}

void MainWindow::encrypt_nullptr()
{
    encrypt_symmetric=Q_NULLPTR;
}

void MainWindow::decrypt()
{

    decrypt_symmetric=new DecryptSymmetric;
    connect(decrypt_symmetric, SIGNAL(close_wndw()), this, SLOT(decrypt_nullptr()));

}

void MainWindow::decrypt_nullptr()
{
    decrypt_symmetric=Q_NULLPTR;
}

void MainWindow::back()
{
    delete_encrypt_decrypt();
    set_registration_authorization();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if (this->decrypt_symmetric) this->decrypt_symmetric->close();
    if (this->encrypt_symmetric) this->encrypt_symmetric->close();
    if (this->make_symmetric_key)this->make_symmetric_key->close();
}
