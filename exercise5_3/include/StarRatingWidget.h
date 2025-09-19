#ifndef STARRATINGWIDGET_H
#define STARRATINGWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPolygonF>

class StarRatingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StarRatingWidget(QWidget *parent = nullptr);

    int getRating() const { return m_rating; }
    void setRating(int rating);

    double getHoverRating() const { return m_hoverRating; }

signals:
    void ratingChanged(int rating);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void drawStar(QPainter &painter, const QPointF &center, double fillRatio, const QColor &color);
    QPolygonF createStarPolygon(const QPointF &center) const;
    double getRatingFromPosition(const QPointF &pos) const;

    int m_rating;
    double m_hoverRating;
    static const int m_starCount = 5;
    static const int m_starSize = 30;
    static const int m_spacing = 5;
};

#endif // STARRATINGWIDGET_H