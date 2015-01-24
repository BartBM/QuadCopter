#-------------------------------------------------
#
# Project created by QtCreator 2014-06-17T23:50:00
#
#-------------------------------------------------

TEMPLATE = app

QT       += core
QT       -= gui

TARGET = imu

CONFIG += c++11

LIBS += -lserial
SOURCES += math/vector3.cpp \
    tests/testvector3.cpp


HEADERS += math/vector3.h
