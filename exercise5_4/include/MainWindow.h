#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "TrafficLightWidget.h"
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    TrafficLightWidget *trafficLight;
    QTimer *timer;
    TrafficLightWidget::LightState currentState;
};
#endif // MAINWINDOW_H