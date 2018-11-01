#ifndef BUSPIRATE_H
#define BUSPIRATE_H

#include <SerialPort.h>
#include <vector>
#include "i2c/i2cdatabus.h"

#define RESET               0b00000010
#define BIN_I2C_MODE        0b00000010
#define BIN_I2C_VERSION     0b00000001
#define BIN_I2C_SPEED       0b01100011  //011000xx – 400kHz = 3
#define BIN_I2C_STARTUP     0b01001000  //0100wxyz – w=power, x=pullups, y=AUX, z=CS
#define BIN_I2C_SHUTDOWN    0b01000000
#define BIN_I2C_STARTBIT    0b00000010
#define BIN_I2C_STOPBIT     0b00000011
#define BIN_I2C_READBYTE    0b00000100
#define BIN_I2C_ACK         0b00000110
#define BIN_I2C_NACK        0b00000111
#define BIN_I2C_BULK_WRITE  0b00010000
#define BIN_I2C_W_THEN_R    0x08

using namespace std;

class BusPirate : public I2CDataBus
{
public:
    BusPirate();
    ~BusPirate();

    void init();
    vector<unsigned char> writeThenRead(int nrBytesToRead, vector<unsigned char> bytesToWrite);

private:
    void initSerial();
    void triggerBitbangMode();
    void setupI2C();
    void startI2C();
    void shutdownI2C();    

    SerialPort*             busPirateSerialPort;
    vector<unsigned char>   dataBuffer;
};

#endif // BUSPIRATE_H
