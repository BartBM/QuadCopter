#ifndef THREEDWIDGET_H
#define THREEDWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QKeyEvent>
#include "inputtransformation.h"

class ThreeDWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    ThreeDWidget(QWidget *parent, InputTransformation* inputTransformation);

protected:
    void initializeGL();
    void resizeGL(int w, int l);
    void paintGL();

private:
    void colorcube();
    void quad();

    QMatrix4x4 projectionMatrix;
    QMatrix4x4 modelview;

    InputTransformation* inputTransformation;
};

#endif // THREEDWIDGET_H
