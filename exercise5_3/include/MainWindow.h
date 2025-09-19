#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "StarRatingWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onRatingChanged(int rating);

private:
    StarRatingWidget *m_starRating;
    QLabel *m_ratingLabel;
    QLabel *m_instructionLabel;
};

#endif // MAINWINDOW_H