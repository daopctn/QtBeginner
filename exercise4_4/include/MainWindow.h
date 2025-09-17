#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "CanvasWidget.h"
#include <QLabel>
#include <QScreen>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void centerWindow();

private slots:
    void updateMousePosition(const QPoint &position);
    void updateDrawingStatus(const QString &status);

private:
    QLabel *statusLabel;
    QLabel *positionLabel;
    CanvasWidget *canvasWidget;
};

#endif // MAINWINDOW_H