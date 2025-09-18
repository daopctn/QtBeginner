#include <ClockWidget.h>
#include <QPainter>
#include <QResizeEvent>
#include <QTime>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this)), time(QTime::currentTime())
{
    // Set up the timer to update every second
    connect(timer, &QTimer::timeout, this, &ClockWidget::updateTime);
    timer->start(1000); // 1 second interval

    // Initial size
    setFixedSize(300, 300);    
}

ClockWidget::~ClockWidget()
{
    delete timer;
}

void ClockWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the clock face
    painter.setBrush(Qt::white);
    painter.drawEllipse(rect());

    // Draw numbers on the clock face
    painter.setFont(QFont("Arial", 12));
    for (int i = 1; i <= 12; ++i)
    {
        painter.save();
        painter.translate(width() / 2, height() / 2);
        painter.rotate(i * 30);
        painter.translate(0, -height() / 2 + 30);
        painter.rotate(-i * 30);
        painter.drawText(-10, 5, QString::number(i));
        painter.restore();
    }

    // Draw the hour , minute and second hands
    painter.save();
    painter.translate(width() / 2, height() / 2);
    painter.rotate(30 * time.hour() + time.minute() / 2.0);
    painter.drawRect(-4, -40, 8, 40);
    painter.restore();

    painter.save();
    painter.translate(width() / 2, height() / 2);
    painter.rotate(6 * time.minute());
    painter.drawRect(-2, -60, 4, 60);
    painter.restore();

    painter.save();
    painter.translate(width() / 2, height() / 2);
    painter.rotate(6 * time.second());
    painter.drawRect(-1, -70, 2, 70);
    painter.restore();
}

void ClockWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}

void ClockWidget::updateTime()
{
    time = QTime::currentTime();
    update();
}