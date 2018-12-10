    #-------------------------------------------------
#
# Project created by QtCreator 2018-12-01T12:36:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

LIBS += -LC:/OpenSSL-Win64/lib -llibssl
LIBS += -LC:/OpenSSL-Win64/lib -lopenssl
LIBS += -LC:/OpenSSL-Win64/lib -llibcrypto
LIBS += -LC:/OpenSSL-Win64/lib -lcapi
LIBS += -LC:/OpenSSL-Win64/lib -ldasync
LIBS += -LC:/OpenSSL-Win64/lib -llibapps
LIBS += -LC:/OpenSSL-Win64/lib -llibcrypto_static
LIBS += -LC:/OpenSSL-Win64/lib -llibssl_static
LIBS += -LC:/OpenSSL-Win64/lib -llibtestutil
LIBS += -LC:/OpenSSL-Win64/lib -lossltest
LIBS += -LC:/OpenSSL-Win64/lib -lpadlock
LIBS += -LC:/OpenSSL-Win64/lib -luitest

INCLUDE += C:/OpenSSL-Win64/include
LIBPATH += C:/OpenSSL-Win64/lib
INCLUDEPATH += C:/OpenSSL-Win64/include

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    symmetric/makesymmetrickey.cpp \
    symmetric/encryptsymmetric.cpp \
    symmetric/decryptsymmetric.cpp \
    asymmetric(RSA)/makeasymmetrickey.cpp \
    asymmetric(RSA)/encryptasymmetric.cpp \
    asymmetric(RSA)/decryptasymmetric.cpp

HEADERS += \
        mainwindow.h \
    symmetric/makesymmetrickey.h \
    symmetric/encryptsymmetric.h \
    symmetric/decryptsymmetric.h \
    asymmetric(RSA)/makeasymmetrickey.h \
    asymmetric(RSA)/encryptasymmetric.h \
    asymmetric(RSA)/decryptasymmetric.h

FORMS += \
        mainwindow.ui \
    symmetric/makesymmetrickey.ui \
    symmetric/encryptsymmetric.ui \
    symmetric/decryptsymmetric.ui \
    asymmetric(RSA)/makeasymmetrickey.ui \
    asymmetric(RSA)/encryptasymmetric.ui \
    asymmetric(RSA)/decryptasymmetric.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
