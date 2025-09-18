#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H
#include <QWidget>
#include <QTimer>
#include <QTime>

class ClockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClockWidget(QWidget *parent = nullptr);
    ~ClockWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QTimer *timer;
    QTime time;
    void updateTime();
};
#endif // CLOCKWIDGET_H