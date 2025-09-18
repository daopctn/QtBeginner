#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "ClockWidget.h"
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ClockWidget *clockWidget;
    QLabel *titleLabel;
};
#endif // MAINWINDOW_H