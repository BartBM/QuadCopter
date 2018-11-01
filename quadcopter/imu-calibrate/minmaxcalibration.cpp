#include "minmaxcalibration.h"

MinMaxCalibration::MinMaxCalibration() : QObject()
{
    this->minMaxAxisValues = new MinMaxAxisValues();
}

MinMaxCalibration::MinMaxCalibration(ChartDataUpdater *chartDataUpdater)
{
    this->minMaxAxisValues = new MinMaxAxisValues();
    this->chartDataUpdater = chartDataUpdater;
}

void MinMaxCalibration::processReading(Vector3<float> axisReading)
{
    this->minMaxAxisValues->valx = axisReading.getX();
    this->minMaxAxisValues->valy = axisReading.getY();
    this->minMaxAxisValues->valz = axisReading.getZ();

    if (axisReading.getX() < this->minMaxAxisValues->getMinX()) {
        this->minMaxAxisValues->minx = axisReading.getX();
    } else if (axisReading.getX() > this->minMaxAxisValues->getMaxX()) {
        this->minMaxAxisValues->maxx = axisReading.getX();
    }

    if (axisReading.getY() < this->minMaxAxisValues->getMinY()) {
        this->minMaxAxisValues->miny = axisReading.getY();
    } else if (axisReading.getY() > this->minMaxAxisValues->getMaxY()) {
        this->minMaxAxisValues->maxy = axisReading.getY();
    }

    if (axisReading.getZ() < this->minMaxAxisValues->getMinZ()) {
        this->minMaxAxisValues->minz = axisReading.getZ();
    } else if (axisReading.getZ() > this->minMaxAxisValues->getMaxZ()) {
        this->minMaxAxisValues->maxz = axisReading.getZ();
    }

    chartDataUpdater->processMinMaxAxisValues(this->minMaxAxisValues);
}

MinMaxAxisValues *MinMaxCalibration::getMinMaxAxisValues()
{
    return this->minMaxAxisValues;
}
