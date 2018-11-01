#ifndef CHARTDATA_H
#define CHARTDATA_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include "minmaxaxisvalues.h"

class ChartData : public QObject
{
    Q_OBJECT
public:
    explicit ChartData(QObject *parent = nullptr);
    void appendXPoint( float x, float y );

signals:

public slots:

private:
    QVector<QPointF> *xData;
    MinMaxAxisValues *minMaxAxisValues;
};

#endif // CHARTDATA_H
