#ifndef I2CDATABUS_H
#define I2CDATABUS_H

#include <vector>

class I2CDataBus
{
public:
    virtual ~I2CDataBus() {}
    virtual void init() = 0;

    virtual std::vector<unsigned char> writeThenRead(int nrBytesToRead, std::vector<unsigned char> bytesToWrite) = 0;
};

#endif // I2CDATABUS_H
