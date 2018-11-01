#ifndef I2CCHIP_H
#define I2CCHIP_H

#include <vector>
#include <iostream>
#include "i2cdatabus.h"

using namespace std;

class I2CChip
{
public:
    I2CChip();
    void init(I2CDataBus* i2cDataBus);

    virtual unsigned char getReadAddr() = 0;
    virtual unsigned char getWriteAddr() = 0;

protected:
    void write(vector<unsigned char> data);

    template<typename T>
    vector<T> read(int nrBytesToRead);

    template<typename T>
    T readValue(unsigned char reg_addr) {
        write({reg_addr});
        return read<T>(0)[0] & 0xFFFFFFFF;
    }

    template<typename T>
    vector<T>readValues(unsigned char reg_addr, int nrBytesToRead) {
        write({reg_addr});
        return read<T>(nrBytesToRead);
    }

    I2CDataBus* i2cDataBus;

};

#endif // I2CCHIP_H
