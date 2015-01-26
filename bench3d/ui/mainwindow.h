#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threedwidget.h"
#include "inputtransformation.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent * event);

private:
    ThreeDWidget* threeDWidget;
    InputTransformation* inputTransformation;
};

#endif // MAINWINDOW_H
