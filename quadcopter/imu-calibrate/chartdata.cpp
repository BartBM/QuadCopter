#include "chartdata.h"

ChartData::ChartData(QObject *parent) : QObject(parent)
{
    this->xData = new QVector<QPointF>(500);
}

void ChartData::appendXPoint(float x, float y) {
    xData->append(QPointF(x, y));

    if (this->xData->count() > 100) {
        this->xData->remove(0);
    }
}
