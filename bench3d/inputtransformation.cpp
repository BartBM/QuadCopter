#include "inputtransformation.h"
#include <iostream>

using namespace std;

InputTransformation::InputTransformation()
{
    angleStep = DEFAULT_ANGLE_STEP;
    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;

    translationStep = DEFAULT_TRANSLATION_STEP;
    xTranslation = 0.0f;
    yTranslation = 0.0f;
    zTranslation = 0.0f;
}


void InputTransformation::increaseAngle(Axis axis)
{
    switch (axis) {
        case Axis::x:
            xAngle += angleStep;
            break;
        case Axis::y:
            yAngle += angleStep;
            break;
        case Axis::z:
            zAngle += angleStep;
            break;
    }
}

void InputTransformation::decreaseAngle(Axis axis)
{
    switch (axis) {
        case Axis::x:
            xAngle -= angleStep;
            break;
        case Axis::y:
            yAngle -= angleStep;
            break;
        case Axis::z:
            zAngle -= angleStep;
            break;
    }
}

float InputTransformation::getAngle(Axis axis)
{
    switch (axis) {
        case Axis::x:
            return xAngle;
        case Axis::y:
            return yAngle;
        case Axis::z:
            return zAngle;
        default:
            return 0.0f;
    }
}

void InputTransformation::increaseTranslation(Axis axis)
{
    switch (axis) {
        case Axis::x:
            xTranslation += translationStep;
            break;
        case Axis::y:
            yTranslation += translationStep;
            break;
        case Axis::z:
            zTranslation += translationStep;
            break;
    }
}

void InputTransformation::decreaseTranslation(Axis axis)
{
    switch (axis) {
        case Axis::x:
            xTranslation -= translationStep;
            break;
        case Axis::y:
            yTranslation -= translationStep;
            break;
        case Axis::z:
            zTranslation -= translationStep;
            break;
    }
}

float InputTransformation::getTranslation(Axis axis)
{
    switch (axis) {
        case Axis::x:
            return xTranslation;
        case Axis::y:
            return yTranslation;
        case Axis::z:
            return zTranslation;
        default:
            return 0.0f;
    }
}
