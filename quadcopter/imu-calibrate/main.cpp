#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRandomGenerator64>
#include "minmaxcalibration.h"
#include "chartdataupdater.h"
#include "chartdata.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "math/vector3.h"

void changeValues(MinMaxCalibration *minMaxCalibration, int timeout)
{
    std::cout << "changing values.. ";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    QRandomGenerator64 randomGenerator;

    for (int i = 0; i < 1000; ++i) {
        Vector3<float> reading(randomGenerator.bounded(-16384, 16384),
                               randomGenerator.bounded(-16384, 16384),
                               randomGenerator.bounded(-16384, 16384));
        minMaxCalibration->processReading(reading);
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    ChartDataUpdater *chartDataUpdater = new ChartDataUpdater();

    MinMaxCalibration *minMaxCalibration = new MinMaxCalibration(chartDataUpdater);
    //qmlRegisterUncreatableType<MinMaxAxisValues>("Module", 1, 0, "MinMaxAxisValues", nullptr);
    //qmlRegisterUncreatableType<MinMaxCalibration>("Module", 1, 0, "MinMaxCalibration", nullptr);
    qmlRegisterUncreatableType<ChartData>("Module", 1, 0, "ChartData", nullptr);

    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("calibration", minMaxCalibration);
    //engine.rootContext()->setContextProperty("dataseries", minMaxDataSeries);
    engine.rootContext()->setContextProperty("chartData", chartDataUpdater->getChartData());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    std::thread threadOne(changeValues, minMaxCalibration, 5);

    return app.exec();
}
