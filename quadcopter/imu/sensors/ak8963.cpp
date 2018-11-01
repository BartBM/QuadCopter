#include "ak8963.h"
#include <bitset>
#include <unistd.h>
#include <stdexcept>

using namespace std;

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

    cout << "\tASA: " << asa.toString() << endl;

}

void AK8963::selfTest()
{
    cout << "[AK8963 selfTest]" << endl;

    setOutputBitSetting(OutputBitSetting::_14BIT);
    setOperationModeSetting(OperationMode::POWER_DOWN);
    setSelfTest(true);
    setOperationModeSetting(OperationMode::SELF_TEST);

    while (!readStatus1().isDataReady()) {
        usleep(500);
    }

    Vector3<double> adjustedReading = readAdjustedMeasurementData();
    setSelfTest(false);
    setOperationModeSetting(OperationMode::POWER_DOWN);

    if (adjustedReading.getX() >= -50 && adjustedReading.getX() <= 50
            && adjustedReading.getY() >= -50 && adjustedReading.getY() <= 50
            && adjustedReading.getZ() >= -800 && adjustedReading.getZ() <= -200) {
        cout << "\tSelf test [PASSED]: " << adjustedReading.toString() << endl;
    } else {
         throw runtime_error("\tSelf test [FAILED]: " + adjustedReading.toString());
    }
}

void AK8963::setSelfTest(bool enabled)
{
    if (enabled) {
        write({ASTC, 0x40});
    } else {
        write({ASTC, 0x00});
    }
    //usleep(1000000);
}

Vector3<short> AK8963::readRawMeasurementData()
{
    Vector3<short> measurementData;

    vector<unsigned char> values = readValues<unsigned char>(HXL, 6);

    measurementData.setY( (((short) values[1]) << 8 | values[0]) * -1 );
    measurementData.setX( ((short) values[3]) << 8 | values[2] );
    measurementData.setZ( ((short) values[5]) << 8 | values[4] );

    return measurementData;
}

Vector3<double> AK8963::adjustMeasurementData(Vector3<short> data)
{
    Vector3<double> correctedData = (Vector3<double>) readRawMeasurementData();
    correctedData = (((Vector3<double>) data) * (((((Vector3<double>) asa - 128.0) * 0.5f) / 128.0) + 1)) * getOutputDataResolution();
    return correctedData;
}

Vector3<double> AK8963::readAdjustedMeasurementData()
{
    return adjustMeasurementData(readRawMeasurementData());
}

double AK8963::getOutputDataResolution() {
    switch (outputBitSetting) {
        case OutputBitSetting::_14BIT:
            return 0.6d;
        case OutputBitSetting::_16BIT:
            return 0.15d;
        default:
            return 0.6d;
    }
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

unsigned char AK8963::getOutputBitSetting()
{
    return static_cast<typename std::underlying_type<OutputBitSetting>::type>(outputBitSetting);
}

