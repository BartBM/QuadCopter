#ifndef MINMAXAXISVALUES_H
#define MINMAXAXISVALUES_H

#include <QObject>

class MinMaxAxisValues : public QObject
{
    Q_OBJECT
public:
    explicit MinMaxAxisValues(QObject *parent = nullptr);    

    float minx, valx, maxx;
    float miny, valy, maxy;
    float minz, valz, maxz;

signals:

public slots:
    float getMinX() { return this->minx; }
    float getX() { return this->valx; }
    float getMaxX() { return this->maxx; }

    float getMinY() { return this->miny; }
    float getY() { return this->valy; }
    float getMaxY() { return this->maxy; }

    float getMinZ() { return this->minz; }
    float getZ() { return this->valz; }
    float getMaxZ() { return this->maxz; }

};

#endif // MINMAXAXISVALUES_H
