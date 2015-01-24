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
#CONFIG   -= app_bundle

LIBS += -lserial
SOURCES += main.cpp \
    sensors/variometer.cpp \
    communication/buspirate.cpp \
    communication/i2c/i2cchip.cpp \
    sensors/mpu9250.cpp \
    math/vector3.cpp \
    sensors/ak8963.cpp

HEADERS += \
    buspirate.h \
    sensors/variometer.h \
    communication/buspirate.h \
    communication/i2c/i2cdatabus.h \
    communication/i2c/i2cchip.h \
    sensors/mpu9250.h \
    math/vector3.h \
    sensors/mpu9250_constants.h \
    sensors/ak8963.h \
    sensors/ak8963_constants.h
