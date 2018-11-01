#ifndef MINMAXDATASERIES_H
#define MINMAXDATASERIES_H

#include <QObject>
#include <QLineSeries>
#include <QTime>
#include "minmaxaxisvalues.h"
#include "chartdata.h"

QT_CHARTS_USE_NAMESPACE

class ChartDataUpdater : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ChartData* chartData READ getChartData NOTIFY chartDataChanged)
public:
    explicit ChartDataUpdater(QObject *parent = nullptr);

signals:
    void chartDataChanged();

public slots:
    void processMinMaxAxisValues(MinMaxAxisValues *values);
    inline ChartData* getChartData() { return chartData; }

private:
    ChartData *chartData;
    QTime time;
    int lastTimeElapsed;

    void emitSeriesDelayed();
};

#endif // MINMAXDATASERIES_H
