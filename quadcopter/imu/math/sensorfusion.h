#ifndef SENSORFUSION_H
#define SENSORFUSION_H

#include "vector3.h"
#include "../events/threadedeventobserver.h"

enum class FusionAlgorithm: unsigned char {
    Madgwick,
    MahonyDCM
};

#define sampleFreq	100.0f          // sample frequency in Hz
#define betaDef		0.1f            // 2 * proportional gain
#define twoKpDef	(2.0f * 0.5f)	// 2 * proportional gain
#define twoKiDef	(2.0f * 0.0f)	// 2 * integral gain


class SensorFusion : public ThreadedEventObserver
{
public:
    SensorFusion();
    ~SensorFusion();

protected:
    void madgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void madgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

    void mahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
    void mahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);

    float invSqrt(float x);

    void logCurrentReading();
    void processEvent(Event* event);

private:
    volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

    //Madgwick
    volatile float beta;			// algorithm gain

    //Mahony
    volatile float twoKp;			// 2 * proportional gain (Kp)
    volatile float twoKi;			// 2 * integral gain (Ki)
    float integralFBx,  integralFBy, integralFBz;
};

#endif // SENSORFUSION_H
