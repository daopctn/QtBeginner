#ifndef EXERCISE1WINDOW_H
#define EXERCISE1WINDOW_H

#include <QWidget>

class Exercise1Window : public QWidget
{
    Q_OBJECT

public:
    Exercise1Window(QWidget *parent = nullptr);
    ~Exercise1Window();

private:
    void centerWindow();
};

#endif // EXERCISE1WINDOW_H