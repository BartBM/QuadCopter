#-------------------------------------------------
#
# Project created by QtCreator 2014-12-05T11:28:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bench3D
TEMPLATE = app

LIBS += -L/usr/local/lib -lGLU

CONFIG += c++11

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    threedwidget.cpp \
    inputtransformation.cpp

HEADERS  += ui/mainwindow.h \
    threedwidget.h \
    inputtransformation.h
