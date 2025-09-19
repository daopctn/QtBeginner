#include "StarRatingWidget.h"
#include <QPaintEvent>
#include <QBrush>
#include <QPen>
#include <cmath>

StarRatingWidget::StarRatingWidget(QWidget *parent)
    : QWidget(parent), m_rating(0), m_hoverRating(-1)
{
    setFixedSize(m_starCount * (m_starSize + m_spacing) - m_spacing, m_starSize);
    setMouseTracking(true);
}

void StarRatingWidget::setRating(int rating)
{
    if (rating < 0) rating = 0;
    if (rating > m_starCount) rating = m_starCount;

    if (m_rating != rating) {
        m_rating = rating;
        update();
        emit ratingChanged(m_rating);
    }
}

void StarRatingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < m_starCount; ++i) {
        QPointF center(i * (m_starSize + m_spacing) + m_starSize / 2.0, m_starSize / 2.0);

        double fillRatio = 0.0;
        QColor color = QColor(200, 200, 200);

        if (m_hoverRating >= 0) {
            double starPos = i + 1;
            double halfStarPos = i + 0.5;

            if (m_hoverRating >= starPos) {
                fillRatio = 1.0;
                color = QColor(255, 215, 0);
            } else if (m_hoverRating >= halfStarPos) {
                fillRatio = 0.5;
                color = QColor(255, 215, 0);
            }
        } else {
            if (m_rating > i) {
                fillRatio = 1.0;
                color = QColor(255, 215, 0);
            }
        }

        drawStar(painter, center, fillRatio, color);
    }
}

void StarRatingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        double rating = getRatingFromPosition(event->position());
        setRating(static_cast<int>(std::ceil(rating)));
    }
}

void StarRatingWidget::mouseMoveEvent(QMouseEvent *event)
{
    double rating = getRatingFromPosition(event->position());
    if (m_hoverRating != rating) {
        m_hoverRating = rating;
        update();
    }
}

void StarRatingWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_hoverRating = -1;
    update();
}

void StarRatingWidget::drawStar(QPainter &painter, const QPointF &center, double fillRatio, const QColor &color)
{
    QPolygonF star = createStarPolygon(center);

    painter.setPen(QPen(Qt::black, 1));

    if (fillRatio > 0) {
        if (fillRatio >= 1.0) {
            painter.setBrush(QBrush(color));
            painter.drawPolygon(star);
        } else {
            painter.setBrush(QBrush(QColor(240, 240, 240)));
            painter.drawPolygon(star);

            painter.setClipRect(center.x() - m_starSize/2.0, center.y() - m_starSize/2.0,
                              m_starSize * fillRatio, m_starSize);
            painter.setBrush(QBrush(color));
            painter.drawPolygon(star);
            painter.setClipping(false);
        }
    } else {
        painter.setBrush(QBrush(QColor(240, 240, 240)));
        painter.drawPolygon(star);
    }
}

QPolygonF StarRatingWidget::createStarPolygon(const QPointF &center) const
{
    QPolygonF star;
    double outerRadius = m_starSize / 2.0 * 0.8;
    double innerRadius = outerRadius * 0.4;

    for (int i = 0; i < 10; ++i) {
        double angle = i * M_PI / 5.0 - M_PI / 2.0;
        double radius = (i % 2 == 0) ? outerRadius : innerRadius;

        double x = center.x() + radius * std::cos(angle);
        double y = center.y() + radius * std::sin(angle);
        star << QPointF(x, y);
    }

    return star;
}

double StarRatingWidget::getRatingFromPosition(const QPointF &pos) const
{
    double x = pos.x();
    if (x < 0) return 0;
    if (x >= width()) return m_starCount;

    double starWidth = m_starSize + m_spacing;
    int starIndex = static_cast<int>(x / starWidth);
    double posInStar = x - starIndex * starWidth;

    if (starIndex >= m_starCount) return m_starCount;

    double rating = starIndex;
    if (posInStar > m_starSize / 2.0) {
        rating += 1.0;
    } else {
        rating += 0.5;
    }

    return rating;
}