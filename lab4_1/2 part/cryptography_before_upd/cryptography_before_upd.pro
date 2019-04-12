#-------------------------------------------------
#
# Project created by QtCreator 2019-04-06T20:39:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cryptography_before_upd
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

INCLUDEPATH+="test/testing/googletest"
INCLUDEPATH+="test/testing/googletest/include"
INCLUDEPATH+="test/testing/googlemock"
INCLUDEPATH+="test/testing/googlemock/include"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    symmetric/decryptsymmetric.cpp \
    symmetric/encryptsymmetric.cpp \
    symmetric/makesymmetrickey.cpp

HEADERS += \
        mainwindow.h \
    symmetric/decryptsymmetric.h \
    symmetric/encryptsymmetric.h \
    symmetric/makesymmetrickey.h

FORMS += \
        mainwindow.ui \
    symmetric/decryptsymmetric.ui \
    symmetric/encryptsymmetric.ui \
    symmetric/makesymmetrickey.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
