#include "MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_instructionLabel = new QLabel("Click on stars to rate (hover for half-star rating):", this);
    m_instructionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_instructionLabel);

    mainLayout->addSpacing(20);

    QHBoxLayout *ratingLayout = new QHBoxLayout();
    ratingLayout->addStretch();

    m_starRating = new StarRatingWidget(this);
    ratingLayout->addWidget(m_starRating);

    ratingLayout->addStretch();
    mainLayout->addLayout(ratingLayout);

    mainLayout->addSpacing(20);

    m_ratingLabel = new QLabel("Current Rating: 0/5", this);
    m_ratingLabel->setAlignment(Qt::AlignCenter);
    m_ratingLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333;");
    mainLayout->addWidget(m_ratingLabel);

    mainLayout->addStretch();

    connect(m_starRating, &StarRatingWidget::ratingChanged,
            this, &MainWindow::onRatingChanged);

    setWindowTitle("Star Rating Widget - Exercise 5.3");
    resize(400, 200);
}

void MainWindow::onRatingChanged(int rating)
{
    m_ratingLabel->setText(QString("Current Rating: %1/5").arg(rating));
}