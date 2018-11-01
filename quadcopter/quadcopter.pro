TEMPLATE = subdirs

SUBDIRS = \
    imu \
    imu-calibrate

imu.subdir = imu
imu-calibrate.subdir = imu-calibrate
imu-calibrate.depends = imu

CONFIG += ordered
