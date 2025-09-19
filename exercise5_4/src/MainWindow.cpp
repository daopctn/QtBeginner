#include "MainWindow.h"
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentState(TrafficLightWidget::RED)
{
    setWindowTitle("Exercise 5.4: Traffic Light Simulation");
    setFixedSize(400, 400);
    // Center the window on the screen
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Add title label
    QLabel *titleLabel = new QLabel("Traffic Light Simulation", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16pt;");
    mainLayout->addWidget(titleLabel);

    // Create and add TrafficLightWidget
    trafficLight = new TrafficLightWidget(this);
    mainLayout->addWidget(trafficLight, 0, Qt::AlignHCenter);

    // Initialize traffic light to RED
    trafficLight->setActiveLight(currentState);

    // Set up timer to change lights every second
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, [this]()
                     {
        static int currentLight = 0;
        switch(currentLight % 3) {
            case 0:
                trafficLight->setActiveLight(TrafficLightWidget::RED);
                currentState = TrafficLightWidget::RED;
                break;
            case 1:
                trafficLight->setActiveLight(TrafficLightWidget::YELLOW);
                currentState = TrafficLightWidget::YELLOW;
                break;
            case 2:
                trafficLight->setActiveLight(TrafficLightWidget::GREEN);
                currentState = TrafficLightWidget::GREEN;
                break;
        }
        currentLight++; });
    timer->start(1000); // Change light every 1000 ms (1 second)
}

MainWindow::~MainWindow()
{
}