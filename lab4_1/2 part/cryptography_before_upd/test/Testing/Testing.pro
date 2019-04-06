QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=console c++14

INCLUDEPATH+="../../"
INCLUDEPATH+="googletest"
INCLUDEPATH+="googletest/include"
INCLUDEPATH+="googlemock"
INCLUDEPATH+="googlemock/include"

SOURCES += \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc \
    main.cpp

