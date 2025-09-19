// TrafficLightWidget.cpp
#include "TrafficLightWidget.h"

TrafficLightWidget::TrafficLightWidget(QWidget *parent)
    : QWidget(parent), m_currentState(OFF)
{
    // Set fixed size for the widget - golden ratio for aesthetics
    setFixedSize(120, 320);

    // Set black background
    setStyleSheet("background-color: black;");
}

void TrafficLightWidget::setActiveLight(LightState state)
{
    m_currentState = state;
    update(); // Trigger repaint
}

void TrafficLightWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int lightDiameter = 80;
    int spacing = 20;
    int xCenter = width() / 2;

    // Calculate positions for three lights
    int redY = spacing;
    int yellowY = spacing + lightDiameter + spacing;
    int greenY = spacing + 2 * (lightDiameter + spacing);

    // Draw border frame
    painter.setPen(QPen(Qt::darkGray, 3));
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(rect().adjusted(2, 2, -2, -2), 10, 10);

    // Draw three lights
    QRect redRect(xCenter - lightDiameter / 2, redY, lightDiameter, lightDiameter);
    QRect yellowRect(xCenter - lightDiameter / 2, yellowY, lightDiameter, lightDiameter);
    QRect greenRect(xCenter - lightDiameter / 2, greenY, lightDiameter, lightDiameter);

    // Draw lights with appropriate active/inactive states
    drawLight(painter, redRect, Qt::red, m_currentState == RED);
    drawLight(painter, yellowRect, Qt::yellow, m_currentState == YELLOW);
    drawLight(painter, greenRect, Qt::green, m_currentState == GREEN);
}

void TrafficLightWidget::drawLight(QPainter &painter, const QRect &rect,
                                   const QColor &color, bool isActive)
{
    // Draw outer ring
    painter.setPen(QPen(Qt::darkGray, 2));

    if (isActive)
    {
        // Active light - bright with glow effect
        QRadialGradient gradient(rect.center(), rect.width() / 2);
        gradient.setColorAt(0, color.lighter(150));
        gradient.setColorAt(0.5, color);
        gradient.setColorAt(1, color.darker(150));
        painter.setBrush(gradient);

        // Add glow effect
        painter.setPen(QPen(color.lighter(120), 3));
    }
    else
    {
        // Inactive light - dark version
        painter.setBrush(color.darker(300));
        painter.setPen(QPen(Qt::darkGray, 2));
    }

    painter.drawEllipse(rect);
}