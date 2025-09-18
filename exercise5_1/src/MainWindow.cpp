#include "MainWindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), clockWidget(new ClockWidget(this)), titleLabel(new QLabel("Analog Clock", this))
{
    // Set up the main widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Configure title label
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    // Add widgets to layout
    layout->addWidget(titleLabel);

    // align the clock widget to center
    layout->addWidget(clockWidget);

    // Set the central widget
    setCentralWidget(centralWidget);

    // Set window properties
    setWindowTitle("Analog Clock Application");

    // Make window size fixed and automatically fit content
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

MainWindow::~MainWindow()
{
    delete clockWidget;
    delete titleLabel;
}
