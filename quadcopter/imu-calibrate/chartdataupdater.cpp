#include "chartdataupdater.h"

ChartDataUpdater::ChartDataUpdater(QObject *parent) : QObject(parent)
{
    lastTimeElapsed = 0;
    this->chartData = new ChartData();
}

void ChartDataUpdater::processMinMaxAxisValues(MinMaxAxisValues *values)
{
    if (time.isNull()) {
        time.start();
    }

    int elapsed = time.elapsed();
    int deltaT = elapsed - lastTimeElapsed;

    this->chartData->appendXPoint(elapsed, values->getX());

    if (deltaT > 10) {
        // emit
    }
}
