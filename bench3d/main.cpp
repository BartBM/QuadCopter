#include <QApplication>
#include "ui/mainwindow.h"
#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    float s = 45.756;

    unsigned char * charPointer = (unsigned char*) &s;

    cout << bitset<8>(charPointer[3]) << endl;
    cout << bitset<8>(charPointer[2]) << endl;
    cout << bitset<8>(charPointer[1]) << endl;
    cout << bitset<8>(charPointer[0]) << endl << endl;

    float result;
    memcpy(&result, charPointer, sizeof(float));
    cout << result << endl;

    return a.exec();
}
