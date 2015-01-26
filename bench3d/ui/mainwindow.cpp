#include "mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    inputTransformation = new InputTransformation();
    threeDWidget = new ThreeDWidget(parent, inputTransformation);

    setCentralWidget(threeDWidget);
}

MainWindow::~MainWindow()
{
    delete threeDWidget;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
        // rotation
        case Qt::Key_Up:
            inputTransformation->increaseAngle(Axis::x);
            break;
        case Qt::Key_Down:
            inputTransformation->decreaseAngle(Axis::x);
            break;
        case Qt::Key_Left:
            inputTransformation->increaseAngle(Axis::z);
            break;
        case Qt::Key_Right:
            inputTransformation->decreaseAngle(Axis::z);
            break;

        // translation
        case Qt::Key_F:
            inputTransformation->decreaseTranslation(Axis::x);
            break;
        case Qt::Key_S:
            inputTransformation->increaseTranslation(Axis::x);
            break;
        case Qt::Key_E:
            inputTransformation->decreaseTranslation(Axis::z);
            break;
        case Qt::Key_D:
            inputTransformation->increaseTranslation(Axis::z);
            break;
        case Qt::Key_Plus:
            inputTransformation->decreaseTranslation(Axis::y);
            break;
        case Qt::Key_Minus:
            inputTransformation->increaseTranslation(Axis::y);
            break;
        default:
            break;
    }
    threeDWidget->update();
}
