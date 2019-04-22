#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(this->size());
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
    /*registration*/{
        registrationBTN=new QPushButton("registration");
        connect(registrationBTN, SIGNAL(clicked()), this, SLOT(registration()));
        MainVLayout->addWidget(registrationBTN);
    }

    /*authorization*/{
        authorizationBTN=new QPushButton("authorization");
        connect(authorizationBTN, SIGNAL(clicked()), this, SLOT(authorization()));
        MainVLayout->addWidget(authorizationBTN);
    }

    /*free version*/{
        free_versionBTN=new QPushButton("free version");
        connect(free_versionBTN, SIGNAL(clicked()), this, SLOT(free_version()));
        MainVLayout->addWidget(free_versionBTN);
    }

    /*exit*/{
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
    QString link = "http://www.google.com";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::authorization()
{
    /**end_authorization();
    return;/**/
    QString login;
    QString password;
    login=QInputDialog::getText(this,"Login", "Write Login");
    if (!login.isEmpty())
    password=QInputDialog::getText(this,"Password", "Write Password");
    if (login=="login"&&password=="password")end_authorization();
    else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Error", "Invalid login or password. Try again?",
                                         QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
               this->authorization();
        }
    }

}

void MainWindow::end_authorization()
{
    delete_registration_authorization();
    is_authorized=true;
    set_encrypt_decrypt();
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
    /*encrypt*/{
        encryptBTN=new QPushButton("encrypt");
        connect(encryptBTN, SIGNAL(clicked()), this, SLOT(encrypt()));
        encryptBTN->setToolTip("encrypt file using file with key or written key");
        MainVLayout->addWidget(encryptBTN);
    }

    /*decrypt*/{
        decryptBTN=new QPushButton("decrypt");
        connect(decryptBTN, SIGNAL(clicked()), this, SLOT(decrypt()));
        decryptBTN->setToolTip("decrypt file using file with key or written key");
        MainVLayout->addWidget(decryptBTN);
    }

    /*key*/{
        create_keyBTN=new QPushButton("create key");
        connect(create_keyBTN, SIGNAL(clicked()), this, SLOT(create_key()));
        create_keyBTN->setToolTip("generete symetric key for save");
        MainVLayout->addWidget(create_keyBTN);
    }

    /*back*/
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
    if (!make_symmetric_key){
        make_symmetric_key= new MakeSymmetricKey;
        connect(make_symmetric_key, SIGNAL(close_wndw()), this, SLOT(key_nullptr()));
    }
    make_symmetric_key->activateWindow();

}

void MainWindow::key_nullptr()
{
    make_symmetric_key=Q_NULLPTR;
}

void MainWindow::encrypt()
{
    if (encrypt_symmetric==Q_NULLPTR){
        encrypt_symmetric=new EncrytpDecryptSymmetric(BF_ENCRYPT,is_authorized);
        encrypt_symmetric->show();
        connect(encrypt_symmetric, SIGNAL(close_wndw()), this, SLOT(encrypt_nullptr()));
    }

    encrypt_symmetric->activateWindow();
}

void MainWindow::encrypt_nullptr()
{
    encrypt_symmetric=Q_NULLPTR;
}

void MainWindow::decrypt()
{
    if (!decrypt_symmetric){
        decrypt_symmetric=new EncrytpDecryptSymmetric(BF_DECRYPT,is_authorized);
        decrypt_symmetric->show();
        connect(decrypt_symmetric, SIGNAL(close_wndw()), this, SLOT(decrypt_nullptr()));
    }

    decrypt_symmetric->activateWindow();

}

void MainWindow::decrypt_nullptr()
{
    decrypt_symmetric=Q_NULLPTR;
}

void MainWindow::back()
{
    delete_encrypt_decrypt();
    set_registration_authorization();
    close_subwindows();
}

void MainWindow::close_subwindows()
{
    if (this->decrypt_symmetric) this->decrypt_symmetric->close();
    if (this->encrypt_symmetric) this->encrypt_symmetric->close();
    if (this->make_symmetric_key)this->make_symmetric_key->close();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    close_subwindows();
}
