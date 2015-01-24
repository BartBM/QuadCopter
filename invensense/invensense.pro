#-------------------------------------------------
#
# Project created by QtCreator 2014-06-17T23:50:00
#
#-------------------------------------------------

TEMPLATE = app

QT       += core
QT       -= gui

TARGET = inv

CONFIG += c++11
#CONFIG   -= app_bundle

LIBS += -lserial
SOURCES += main.cpp \
    communication/buspirate.cpp \
    communication/i2c/i2cchip.cpp \
    sensors/inv_mpu.cpp \
    sensors/inv_dmp.cpp \
    math/vector3.cpp


HEADERS += \
    buspirate.h \
    communication/buspirate.h \
    communication/i2c/i2cdatabus.h \
    communication/i2c/i2cchip.h \
    sensors/inv_mpu.h \
    sensors/inv_dmp.h \
    sensors/inv_dmp_map.h \
    sensors/inv_dmp_key.h \
    math/vector3.h 

