#include "MainWindow.h"
#include <QVBoxLayout>
#include "ProgressRing.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    ProgressRing *progressRing = new ProgressRing(this);
    layout->addWidget(progressRing);

    setWindowTitle("Progress Ring Example");
    resize(300, 300);
}
MainWindow::~MainWindow()
{
}