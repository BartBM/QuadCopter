#ifndef AK8963_H
#define AK8963_H

#include "../communication/i2c/i2cchip.h"
#include "../communication/i2c/i2cdatabus.h"
#include "../math/vector3.h"
#include "ak8963_constants.h"
#include <sstream>

enum class OperationMode : unsigned char
{
    POWER_DOWN = 0b00000000,
    SINGLE_MEASUREMENT = 0b00000001,
    CONT_MEASUREMENT1 = 0b00000010,
    CONT_MEASUREMENT2 = 0b00000110,
    EXTERNAL_TRIGGER = 0b00000100,
    SELF_TEST = 0b00001000,
    FUSE_ROM = 0b00001111
};

enum class OutputBitSetting : unsigned char
{
    _14BIT = 0b00000000,
    _16BIT = 0b00010000
};

class RegStatus1
{
public:
    RegStatus1() {}
    void parse(unsigned char value)
    {
        dataReady = value & 1;
        dataOverrun = value & (1 << 1);
    }

    bool isDataReady() { return dataReady; }
    bool isDataOverrun() { return dataOverrun; }

    string toString()
    {
        stringstream ss;
        ss << "[RegStatus1]" << endl;
        ss << "Data ready: " << dataReady << endl;
        ss << "Data overrun: " << dataOverrun << endl;
        return ss.str();
    }

    bool dataReady;
    bool dataOverrun;
};

class RegStatus2
{
public:
    RegStatus2() {}
    void parse(unsigned char value)
    {
        magneticSensorOverflow = value & (1<<3);
        outputBitSetting = (value & (1<<4)) ? OutputBitSetting::_16BIT : OutputBitSetting::_14BIT;
    }

    bool isMagneticSensorOverflow() { return magneticSensorOverflow; }
    OutputBitSetting getOutputBitSetting() { return outputBitSetting; }

    string toString()
    {
        stringstream ss;
        ss << "[RegStatus2]" << endl;
        ss << "Magnetic sensor overflow: " << ((magneticSensorOverflow) ? "yes" : "no") << endl;
        ss << "Output bitsetting: ";

        switch (outputBitSetting) {
            case OutputBitSetting::_14BIT:
                ss << "14 bit" << endl;
                break;
            case OutputBitSetting::_16BIT:
                ss << "16 bit" << endl;
                break;
        }
        return ss.str();
    }

private:
    bool magneticSensorOverflow;
    OutputBitSetting outputBitSetting;
};

class AK8963 : public I2CChip
{
public:
    AK8963();
    ~AK8963();

    void init(I2CDataBus *i2cDataBus);
    void setOperationModeSetting(OperationMode operationMode);
    void setOutputBitSetting(OutputBitSetting outputBitSetting);
    void deviceId();
    void configure();
    void readSensitivityAdjustmentValues();
    void selfTest();
    void setSelfTest(bool enabled);
    Vector3<short> readRawMeasurementData();
    Vector3<double> adjustMeasurementData(Vector3<short> data);
    Vector3<double> readAdjustedMeasurementData();
    RegStatus1 readStatus1();
    RegStatus2 readStatus2();    

    unsigned char getStartReadAddr() { return ST1; }
    unsigned char getSlaveAddr() { return AK8963_ADDR; }
    unsigned char getReadAddr() { return AK8963_READ_ADDR; }
    unsigned char getWriteAddr() { return AK8963_WRITE_ADDR; }

private:
    Vector3<unsigned char> asa;
    OperationMode operationMode;
    OutputBitSetting outputBitSetting;
};

#endif // AK8963_H
