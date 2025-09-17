#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Exercise 4.4: Drawing Canvas"); // Set window title
    centerWindow();
    resize(800, 600); // Set initial window size
    canvasWidget = new CanvasWidget(this);
    setCentralWidget(canvasWidget);
    positionLabel = new QLabel("Position: (0, 0)", this);
    positionLabel->setMinimumWidth(150);
    positionLabel->setAlignment(Qt::AlignLeft);
    statusLabel = new QLabel("Status: Ready", this);
    statusLabel->setAlignment(Qt::AlignRight);
    connect(canvasWidget, &CanvasWidget::mousePositionChanged,
            this, &MainWindow::updateMousePosition);
    connect(canvasWidget, &CanvasWidget::drawingStatusChanged,
            this, &MainWindow::updateDrawingStatus);

    // Create status bar to hold the labels
    QWidget *statusWidget = new QWidget();
    QHBoxLayout *statusLayout = new QHBoxLayout(statusWidget);
    statusLayout->addWidget(positionLabel);
    statusLayout->addStretch(); // Add space between labels
    statusLayout->addWidget(statusLabel);
    statusBar()->addWidget(statusWidget);
}

MainWindow::~MainWindow()
{
}

// Helper function to center the window on the screen
void MainWindow::centerWindow()
{
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    move(x, y);
}

void MainWindow::updateMousePosition(const QPoint &position)
{
    positionLabel->setText(QString("Position: (%1, %2)").arg(position.x()).arg(position.y()));
}

void MainWindow::updateDrawingStatus(const QString &status)
{
    statusLabel->setText(QString("Status: %1").arg(status));
}