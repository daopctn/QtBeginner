#include "exercise1window.h"
#include <QApplication>
#include <QScreen>

Exercise1Window::Exercise1Window(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("My First Qt Window");
    setFixedSize(400, 300);
    centerWindow();
}

Exercise1Window::~Exercise1Window()
{
}

void Exercise1Window::centerWindow()
{
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    
    move(x, y);
}