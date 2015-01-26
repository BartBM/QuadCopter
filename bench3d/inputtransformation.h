#ifndef INPUTTRANSFORMATION_H
#define INPUTTRANSFORMATION_H

#define DEFAULT_ANGLE_STEP 5.0f
#define DEFAULT_TRANSLATION_STEP 0.1f

enum class Axis {
    x,
    y,
    z
};

class InputTransformation
{
public:
    InputTransformation();

    void increaseAngle(Axis axis);
    void decreaseAngle(Axis axis);
    float getAngle(Axis axis);

    void increaseTranslation(Axis axis);
    void decreaseTranslation(Axis axis);
    float getTranslation(Axis axis);

private:
    float xAngle, yAngle, zAngle;
    float xTranslation, yTranslation, zTranslation;
    float angleStep, translationStep;
};

#endif // INPUTTRANSFORMATION_H
