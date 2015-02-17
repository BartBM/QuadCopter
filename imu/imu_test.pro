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
SOURCES += \
    communication/buspirate.cpp \
    communication/i2c/i2cchip.cpp \
    sensors/variometer.cpp \
    sensors/mpu9250.cpp \
    sensors/ak8963.cpp \
    math/vector3.cpp \
    math/sensorfusion.cpp \
    events/eventdispatcher.cpp \
    events/eventobserver.cpp \
    events/threadedeventobserver.cpp \
    events/imuevent.cpp \    
    tests/testvector3.cpp \
    tests/mockthreadedeventobserver.cpp \
    tests/testevents.cpp \
    tests/test.cpp

HEADERS += \
    buspirate.h \
    communication/buspirate.h \
    communication/i2c/i2cdatabus.h \
    communication/i2c/i2cchip.h \
    sensors/variometer.h \
    sensors/mpu9250.h \
    sensors/mpu9250_constants.h \
    sensors/ak8963.h \
    sensors/ak8963_constants.h \
    math/sensorfusion.h \
    math/vector3.h \
    events/eventdispatcher.h \
    events/eventobserver.h \
    events/threadedeventobserver.h \
    events/event.h \
    events/imuevent.h \
    tests/catch.h \
    tests/mockthreadedeventobserver.h \
    tests/mockevent.h
