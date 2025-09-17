#include "CanvasWidget.h"
#include <QPainter>
#include <QPaintEvent>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setMouseTracking(true);
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit mousePositionChanged(event->pos());

    if (event->buttons() & Qt::LeftButton)
    {
        currentPath.append(event->pos());
        update();
        emit drawingStatusChanged("Drawing");
    }
}
void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        currentPath.clear();
        currentPath.append(event->pos());
        update();
        emit drawingStatusChanged("Drawing");
    }
    else if (event->button() == Qt::RightButton)
    {
        paths.clear();
        currentPath.clear();
        update();
        emit drawingStatusChanged("Canvas cleared");
    }
}
void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !currentPath.isEmpty())
    {
        paths.append(currentPath);
        currentPath.clear();
        update();
        emit drawingStatusChanged("Ready");
    }
    else if (event->button() == Qt::RightButton)
    {
        emit drawingStatusChanged("Ready");
    }
}
void CanvasWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw all stored paths
    painter.setPen(QPen(Qt::black, 2));
    for (const auto &path : paths)
    {
        for (int i = 1; i < path.size(); ++i)
        {
            painter.drawLine(path[i - 1], path[i]);
        }
    }

    // Draw the current path
    if (!currentPath.isEmpty())
    {
        painter.setPen(QPen(Qt::red, 2));
        for (int i = 1; i < currentPath.size(); ++i)
        {
            painter.drawLine(currentPath[i - 1], currentPath[i]);
        }
    }
}