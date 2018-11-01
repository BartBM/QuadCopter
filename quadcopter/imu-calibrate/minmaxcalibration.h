#ifndef MINMAXCALIBRATION_H
#define MINMAXCALIBRATION_H

#include <QObject>
#include "minmaxaxisvalues.h"
#include "math/vector3.h"
#include "chartdataupdater.h"

class MinMaxCalibration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MinMaxAxisValues *minMaxAxisValues READ getMinMaxAxisValues NOTIFY minMaxAxisValuesChanged)
public:
    explicit MinMaxCalibration();
    MinMaxCalibration(ChartDataUpdater *chartDataUpdater);
    void processReading(Vector3<float> axisReading);

signals:
    void minMaxAxisValuesChanged();

public slots:
    MinMaxAxisValues *getMinMaxAxisValues();

private:
    MinMaxAxisValues *minMaxAxisValues;
    ChartDataUpdater *chartDataUpdater;
};

#endif // MINMAXCALIBRATION_H
