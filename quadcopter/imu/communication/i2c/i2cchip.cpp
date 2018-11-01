#include "i2cchip.h"
#include <stdexcept>

I2CChip::I2CChip()
{
}

void I2CChip::init(I2CDataBus* i2cDataBus)
{
    this->i2cDataBus = i2cDataBus;
}

void I2CChip::write(vector<unsigned char> data)
{
    data.insert(data.begin(), getWriteAddr());
    i2cDataBus->writeThenRead(0, data);
}

template<>
vector<unsigned char> I2CChip::read<unsigned char>(int nrBytesToRead)
{
    if (nrBytesToRead == 0) nrBytesToRead = 1;

    vector<unsigned char> v = i2cDataBus->writeThenRead(nrBytesToRead, {getReadAddr()});
    return v;
}

template<>
vector<unsigned int> I2CChip::read<unsigned int>(int nrBytesToRead)
{
    if (nrBytesToRead == 0) nrBytesToRead = 4;

    vector<unsigned char> input = read<unsigned char>(nrBytesToRead);
    if (input.size() % 4 != 0){
        throw runtime_error("Unsigned char vector cannot be converted to int array");
    }

    vector<unsigned int> output;
    for (unsigned int i=0; i<input.size(); i++) {
        unsigned int value = input.at(i) << 24;
        value += (input.at(++i)<< 16);
        value += (input.at(++i)<< 8);
        output.push_back(value | input.at(++i));
    }
    return output;
}

template<>
vector<int> I2CChip::read<int>(int nrBytesToRead)
{
    if (nrBytesToRead == 0) nrBytesToRead = 3;

    vector<unsigned char> input = read<unsigned char>(nrBytesToRead);
    if (input.size() % 3 != 0){
        throw runtime_error("Unsigned char vector cannot be converted to int array");
    }

    vector<int> output;
    for (unsigned int i=0; i<input.size(); i++) {
        int value = input.at(i) << 16;
        value += (input.at(++i)<< 8);
        output.push_back(value | input.at(++i));
    }
    return output;
}

template<>
vector<unsigned short> I2CChip::read<unsigned short>(int nrBytesToRead)
{
    if (nrBytesToRead == 0) nrBytesToRead = 2;

    vector<unsigned char> input = read<unsigned char>(nrBytesToRead);
    if (input.size() % 2 != 0){
        throw runtime_error("Unsigned char vector cannot be converted to short array");
    }

    vector<unsigned short> output;
    for (unsigned int i=0; i<input.size(); i++) {
        unsigned short value = input.at(i) << 8;
        output.push_back(value | input.at(++i));
    }

    return output;
}

template<typename T>
vector<T> I2CChip::read(int nrBytesToRead)
{
    throw runtime_error("Not specialization found: vector<T> I2CChip::read(int nrBytesToRead)");
}
