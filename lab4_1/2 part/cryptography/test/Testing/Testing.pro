QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=console c++14

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

INCLUDEPATH+="../../"
INCLUDEPATH+="googletest"
INCLUDEPATH+="googletest/include"
INCLUDEPATH+="googlemock"
INCLUDEPATH+="googlemock/include"

SOURCES += \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc \
    main.cpp \
    ../../main.cpp \
    ../../mainwindow.cpp \
    ../../symmetric/encrytpdecryptsymmetric.cpp \
    ../../symmetric/makesymmetrickey.cpp


FORMS += \
    ../../mainwindow.ui \
    ../../symmetric/encrytpdecryptsymmetric.ui \
    ../../symmetric/makesymmetrickey.ui


HEADERS += \
    ../../mainwindow.h \
    ../../symmetric/encrytpdecryptsymmetric.h \
    ../../symmetric/makesymmetrickey.h


