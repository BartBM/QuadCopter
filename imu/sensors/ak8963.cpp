#include "ak8963.h"
#include <bitset>
#include <unistd.h>

AK8963::AK8963() : I2CChip()
{
    cout << endl << "==> AK8963 Magnetometer" << endl;
    operationMode = OperationMode::SINGLE_MEASUREMENT;
    outputBitSetting = OutputBitSetting::_16BIT;
}

AK8963::~AK8963()
{

}

void AK8963::init(I2CDataBus *i2cDataBus)
{
    I2CChip::init(i2cDataBus);
}

void AK8963::setOperationModeSetting(OperationMode operationMode)
{
    cout << "Changing operation mode to: " << bitset<8>((unsigned char) operationMode) << endl;
    this->operationMode = operationMode;
    write({CNTL1, (unsigned char) ((unsigned char) operationMode | (unsigned char) outputBitSetting)});
}

void AK8963::setOutputBitSetting(OutputBitSetting outputBitSetting)
{
    cout << "Changing output bit setting: " << bitset<8>((unsigned char) outputBitSetting) << endl;
    this->outputBitSetting = outputBitSetting;
    write({CNTL1, (unsigned char) ((unsigned char) operationMode | (unsigned char) outputBitSetting)});
}

void AK8963::deviceId()
{
    cout << "[AK8963 deviceId]" << endl;
    cout << "\tWIA: " << hex << (int) readValue<unsigned char>(WIA) << endl;
}

void AK8963::configure()
{
    cout << "[AK8963 configure]" << endl;
    deviceId();
    readSensitivityAdjustmentValues();
    usleep(20000);
}

void AK8963::readSensitivityAdjustmentValues()
{
    cout << "[AK8963 readSensitivityAdjustmentValues]" << endl;

    setOperationModeSetting(OperationMode::FUSE_ROM);

    asa.setX(readValue<unsigned char>(ASAX));
    asa.setY(readValue<unsigned char>(ASAY));
    asa.setZ(readValue<unsigned char>(ASAZ));

    cout << "asa: " << asa.toString() << endl;

}

Vector3<short> AK8963::readRawMeasurementData()
{
    Vector3<short> measurementData;

    //cout << bitset<8>(readValue<unsigned char>(HXH)) << bitset<8>(readValue<unsigned char>(HXL)) << endl;
    vector<unsigned char> values = readValues<unsigned char>(HXL, 6);

    //cout << bitset<8>(values[1]) << bitset<8>(values[0]) << endl;
    measurementData.setX( ((short) values[1]) << 8 | values[0] );
    measurementData.setY( ((short) values[3]) << 8 | values[2] );
    measurementData.setZ( ((short) values[5]) << 8 | values[4] );

    //measurementData.setX( ((readValue<unsigned char>(HXH) << 8) & 0xFF00) | (readValue<unsigned char>(HXL) & 0xFF) );
    //measurementData.setY( ((readValue<unsigned char>(HYH) << 8) & 0xFF00) | (readValue<unsigned char>(HYL) & 0xFF) );
    //measurementData.setZ( ((readValue<unsigned char>(HZH) << 8) & 0xFF00) | (readValue<unsigned char>(HZL) & 0xFF) );

    return measurementData;
}

Vector3<double> AK8963::adjustMeasurementData(Vector3<short> data)
{
    Vector3<double> correctedData = (Vector3<double>) readRawMeasurementData();
    correctedData = ((Vector3<double>) data) * (((((Vector3<double>) asa - 128) * 0.5f) / 128) + 1);
    return correctedData;
}

Vector3<double> AK8963::readAdjustedMeasurementData()
{
    return adjustMeasurementData(readRawMeasurementData());
}

RegStatus2 AK8963::readStatus2()
{
    RegStatus2 regStatus2;
    regStatus2.parse(readValue<unsigned char>({ST2}));
    return regStatus2;
}

RegStatus1 AK8963::readStatus1()
{
    RegStatus1 regStatus1;
    regStatus1.parse(readValue<unsigned char>({ST1}));
    return regStatus1;
}

