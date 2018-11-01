#include "variometer.h"
#include <unistd.h>

Variometer::Variometer() : I2CChip()
{
    cout << endl << "==> variometer" << endl;
}

void Variometer::init(I2CDataBus* i2cDataBus)
{
    I2CChip::init(i2cDataBus);
    reset();
    readCalibrationData();
    calcTempCompensatedPressure();
}

void Variometer::reset()
{

}

void Variometer::calcTempCompensatedPressure()
{
    write({0x48});
    int d1 = readValue<int>(0x00);
    cout << dec << "d1: " << d1 << endl;

    write({0x58});
    int d2 = readValue<int>(0x00);
    cout << dec <<  "d2: " << d2 << endl;

    int dT = d2 - (c5 * 256);
    cout << "dT: " << dec << dT << endl;

    int temp = 2000 + dT * c6 / 8388608;
    cout << "temp: " << dec << temp << endl;

    long long int off = c2 * 65536LL + (c4 * dT) / 128;
    cout << "off: " << dec << off << endl;

    long long int sens = c1 * 32768LL + (c3 * dT) / 256;
    cout << "sens: " << dec << sens << endl;

    int p = (d1 * sens / 2097152 - off) / 32768;
    cout << "pressure (mBar): " << dec << p << endl;

    secondOrderTempCompensation();
}

void Variometer::secondOrderTempCompensation()
{

}

void Variometer::readCalibrationData()
{
    c1 = readValue<unsigned short>(0xA2);
    cout << "C1: " << dec << c1 << endl;

    c2 = readValue<unsigned short>(0xA4);
    cout << "C2: " << dec << c2 << endl;

    c3 = readValue<unsigned short>(0xA6);
    cout << "C3: " << dec << c3 << endl;

    c4 = readValue<unsigned short>(0xA8);
    cout << "C4: " << dec << c4 << endl;

    c5 = readValue<unsigned short>(0xAA);
    cout << "C5: " << dec << c5 << endl;

    c6 = readValue<unsigned short>(0xAC);
    cout << "C6: " << dec << c5 << endl;

    crc = readValue<unsigned short>(0xAE);
    cout << "CRC: " << dec << c5 << endl;
}
