#include "buspirate.h"
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <unistd.h>

BusPirate::BusPirate()
{
    busPirateSerialPort = nullptr;
}

BusPirate::~BusPirate()
{
    if (busPirateSerialPort == nullptr) {
        return;
    }

    shutdownI2C();
    if (busPirateSerialPort->IsOpen()) {
        busPirateSerialPort->Close();
    }

    delete busPirateSerialPort;
}

void BusPirate::init()
{
    try {
        initSerial();
        triggerBitbangMode();
        setupI2C();
        startI2C();
        usleep(10000);
    } catch (const SerialPort::OpenFailed ex) {
        cout << ex.what() << endl;
    } catch (const std::exception& ex) {
        cout << ex.what() << endl;

        if (busPirateSerialPort->IsOpen()) {
            busPirateSerialPort->Close();
        }
        //TODO: should not exit
        exit(0);
    }
}

void BusPirate::initSerial()
{
    cout << "==> opening serial port /dev/ttyUSB0" << endl;
    busPirateSerialPort = new SerialPort("/dev/ttyUSB0");
    busPirateSerialPort->Open(SerialPort::BAUD_115200);

    if (!busPirateSerialPort->IsOpen()) {
        throw runtime_error("unable to open serial port");
    }
}

void BusPirate::triggerBitbangMode() {
    cout << endl << "==> triggerBitbangMode" << endl;

    for (int i=0; i<25; i++) {
        busPirateSerialPort->WriteByte(0x00);
        try {
            busPirateSerialPort->Read(dataBuffer, 5, 100);
        } catch(SerialPort::ReadTimeout &e) {
            cout << ".";
            cout.flush();
            continue;
        }

        char received[6];
        memcpy(&received, &dataBuffer[0], 5);
        received[5] = '\0';

        if (strncmp("BBIO1", received, 5) == 0) {
            return;
        }
    }

    throw runtime_error("unable to enter I2C bitbang mode");
}

void BusPirate::setupI2C()
{
    cout << endl << "==> enterBinaryI2CMode" << endl;
    busPirateSerialPort->WriteByte(BIN_I2C_MODE);

    busPirateSerialPort->Read(dataBuffer, 4, 100);
    dataBuffer.push_back('\0');
    cout << "BIN_I2C_MODE status:\t" << &dataBuffer[0] << endl;

    busPirateSerialPort->WriteByte(BIN_I2C_VERSION);
    busPirateSerialPort->Read(dataBuffer, 4, 100);
    dataBuffer.push_back('\0');
    cout << "BIN_I2C_VERSION status:\t" << &dataBuffer[0] << endl;

    busPirateSerialPort->WriteByte(BIN_I2C_SPEED);
    unsigned char status = busPirateSerialPort->ReadByte(100);
    cout << "BIN_I2C_SPEED status:\t" << (int) status << endl;

}

void BusPirate::startI2C()
{
    busPirateSerialPort->WriteByte(BIN_I2C_STARTUP);
    unsigned char status = busPirateSerialPort->ReadByte(100);
    cout << "BIN_I2C_STARTUP status: " << (int) status << endl;
    usleep(50000);
}

void BusPirate::shutdownI2C()
{
    cout << endl << "==> shutdown I2C" << endl;
    busPirateSerialPort->WriteByte(BIN_I2C_SHUTDOWN);
    unsigned char status = busPirateSerialPort->ReadByte(100);
    cout << "BIN_I2C_SHUTDOWN status: " << (int) status << endl;
}

vector<unsigned char> BusPirate::writeThenRead(int nrBytesToRead, vector<unsigned char> bytesToWrite)
{
    busPirateSerialPort->WriteByte(BIN_I2C_W_THEN_R);

    busPirateSerialPort->WriteByte(bytesToWrite.size() >> 0x10);
    busPirateSerialPort->WriteByte(bytesToWrite.size() &  0x00FF);

    busPirateSerialPort->WriteByte(nrBytesToRead >> 0x10);
    busPirateSerialPort->WriteByte(nrBytesToRead &  0x00FF);

    //cout << endl << "Write:\t";
    for (unsigned char& value : bytesToWrite) {
        busPirateSerialPort->WriteByte(value);
        //cout << uppercase << hex << (int) value << " ";
    }
    //cout << endl;
    unsigned char status = busPirateSerialPort->ReadByte(100);


    if ((int) status != 1) {
        //cout << "Status:\tNOK" << endl;
        throw runtime_error("BusPirate::writeThenRead -> wrong status");
    }

    vector<unsigned char> bytesRead;
    //cout << "Read:\t";
    for (int i=0; i<nrBytesToRead; i++) {
        status = busPirateSerialPort->ReadByte(100);
        //cout << uppercase << hex << (int) status << " ";
        bytesRead.push_back(status);
    }
    //cout << endl;
    return bytesRead;

}

//void trySerialStream() {
//    cout << "trySerialStream" << endl;
//    SerialStream busPirateStream("/dev/ttyUSB0");
//    busPirateStream.SetBaudRate(SerialStreamBuf::BAUD_115200);
//    busPirateStream.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);

//    if (busPirateStream.IsOpen()) {
//        cout << "communication to bus pirate open" << endl;
//    } else {
//        cout << "fail" << endl;
//    }

//    string str;
//    for (int i=0; i<20; i++) {
//        cout << "byte written" << endl;
//        busPirateStream << 0x00;
//        usleep(10);

//        if (busPirateStream.rdbuf()->in_avail() > 0) {
//            busPirateStream >> str;
//            cout << "read: " << str << endl;
//        }
//    }

//    busPirateStream.Close();
//}

/**
 * Write [0xEE 0xA2]
**/

//    cout << endl << "WRITE: " << "start bit" << " ";
//    busPirateSerialPort.WriteByte(BIN_I2C_STARTBIT);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (((int) status == 1)? "OK" : "NOK") << endl;

//    busPirateSerialPort.WriteByte(BIN_I2C_BULK_WRITE | 0x1); // send 2 bytes
//    status = busPirateSerialPort.ReadByte(100);
//    cout << "BIN_I2C_BULK_WRITE status: " << (int) status << endl;

//    busPirateSerialPort.WriteByte(0xEE);
//    cout << "0xEE ";
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (status == '\0' ? "ACK" : "NACK") << endl;

//    busPirateSerialPort.WriteByte(0xA2);
//    cout << "0xA2 ";
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (status == '\0' ? "ACK" : "NACK") << endl;

//    cout << "WRITE: " << "stop bit" << " ";
//    busPirateSerialPort.WriteByte(BIN_I2C_STOPBIT);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (((int) status == 1)? "OK" : "NOK") << endl;

/**
 * Write [0xEF r:2]
**/

//    cout << endl << "WRITE: " << "start bit" << " ";
//    busPirateSerialPort.WriteByte(BIN_I2C_STARTBIT);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (((int) status == 1)? "OK" : "NOK") << endl;

//    busPirateSerialPort.WriteByte(BIN_I2C_BULK_WRITE); // send 1 byte
//    status = busPirateSerialPort.ReadByte(100);
//    cout << "BIN_I2C_BULK_WRITE status: " << (int) status << endl;

//    busPirateSerialPort.WriteByte(0xEF);
//    cout << "0xEF ";
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (status == '\0'? "ACK" : "NACK") << endl;

//    busPirateSerialPort.WriteByte(BIN_I2C_READBYTE);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (int) status << endl;
//    busPirateSerialPort.WriteByte(BIN_I2C_ACK);

//    busPirateSerialPort.WriteByte(BIN_I2C_READBYTE);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (int) status << endl;
//    busPirateSerialPort.WriteByte(BIN_I2C_ACK);

//    busPirateSerialPort.WriteByte(BIN_I2C_READBYTE);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (int) status << endl;
//    busPirateSerialPort.WriteByte(BIN_I2C_ACK);

//    busPirateSerialPort.WriteByte(BIN_I2C_READBYTE);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (int) status << endl;
//    busPirateSerialPort.WriteByte(BIN_I2C_NACK);

//    cout << "WRITE: " << "stop bit" << " ";
//    busPirateSerialPort.WriteByte(BIN_I2C_STOPBIT);
//    status = busPirateSerialPort.ReadByte(100);
//    cout << (((int) status == 1)? "OK" : "NOK") << endl;

