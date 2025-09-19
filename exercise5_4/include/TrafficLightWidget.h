// TrafficLightWidget.h
#ifndef TRAFFICLIGHTWIDGET_H
#define TRAFFICLIGHTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class TrafficLightWidget : public QWidget
{
    Q_OBJECT

public:
    enum LightState
    {
        RED,
        YELLOW,
        GREEN,
        OFF
    };

    explicit TrafficLightWidget(QWidget *parent = nullptr);

    void setActiveLight(LightState state);
    LightState getActiveLight() const { return m_currentState; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    LightState m_currentState;

    void drawLight(QPainter &painter, const QRect &rect, const QColor &color, bool isActive);
};

#endif // TRAFFICLIGHTWIDGET_H