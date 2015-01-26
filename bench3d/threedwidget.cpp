#include "threedwidget.h"
#include <iostream>

#include <GL/glu.h>


using namespace std;

ThreeDWidget::ThreeDWidget(QWidget* parent, InputTransformation *inputTransformation) : QOpenGLWidget(parent)
{
    this->inputTransformation = inputTransformation;
}

void ThreeDWidget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    //glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_MULTISAMPLE);
    //static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void ThreeDWidget::resizeGL(int w, int h)
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, w * retinaScale, h * retinaScale);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float zoom = 1.0f;
    gluPerspective(zoom*45.0f,-(GLfloat)w/(GLfloat)h,0.1f,100.0f);

    //gluLookAt(-5.d, -5.0d, -5.0d, 0.0d, 0.0d, 0.0d, 0.0d, 1.0d, 0.0d);
    glMatrixMode(GL_MODELVIEW);
}

void ThreeDWidget::paintGL()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);


    //modelview.rotate(, 0.0f, 1.0f, 0.0f);

    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -10.0f);
    glTranslatef(inputTransformation->getTranslation(Axis::x), inputTransformation->getTranslation(Axis::y), inputTransformation->getTranslation(Axis::z));

    //glRotatef(10.0f, 1.0f, 1.0f, 1.0f);
    glRotatef(inputTransformation->getAngle(Axis::x), 1.0f, 0.0f, 0.0f);
    glRotatef(inputTransformation->getAngle(Axis::z), 0.0f, 0.0f, 1.0f);

    quad();
}

void ThreeDWidget::quad()
{
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f( 1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f,  1.0f);
        glVertex3f( 1.0f, 1.0f,  1.0f);

        // Bottom face (y = -1.0f)
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);

        // Front face  (z = 1.0f)
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f( 1.0f,  1.0f, 1.0f);
        glVertex3f(-1.0f,  1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f( 1.0f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);

        // Left face (x = -1.0f)
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);

        // Right face (x = 1.0f)
        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glVertex3f(1.0f,  1.0f, -1.0f);
        glVertex3f(1.0f,  1.0f,  1.0f);
        glVertex3f(1.0f, -1.0f,  1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
}



