#ifndef VARIOMETER_H
#define VARIOMETER_H

#include "communication/i2c/i2cdatabus.h"
#include "communication/i2c/i2cchip.h"

#define WRITE_ADDR 0xEE
#define READ_ADDR  0xEF

class Variometer : public I2CChip
{
public:
    Variometer();
    void init(I2CDataBus *i2cDataBus);

    unsigned char getReadAddr() { return READ_ADDR; }
    unsigned char getWriteAddr() { return WRITE_ADDR; }

private:
    void reset();
    void readCalibrationData();
    void calcTempCompensatedPressure();
    void secondOrderTempCompensation();

    unsigned short  c1, c2, c3, c4, c5, c6, crc;
    unsigned int    d1, d2;
    int dt, temp, pressure;
    long long int off, sens;

};

#endif // VARIOMETER_H
