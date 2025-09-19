#include "ProgressRing.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QFont>

ProgressRing::ProgressRing(QWidget *parent)
    : QWidget(parent), m_progress(0), m_targetProgress(0)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ProgressRing::onTimeout);

    m_animation = new QPropertyAnimation(this, "progress", this);
    m_animation->setDuration(2000);
    m_animation->setEasingCurve(QEasingCurve::OutQuad);

    m_startButton = new QPushButton("Start", this);
    connect(m_startButton, &QPushButton::clicked, this, &ProgressRing::onStartButtonClicked);

    m_stopButton = new QPushButton("Stop", this);
    connect(m_stopButton, &QPushButton::clicked, this, &ProgressRing::onStopButtonClicked);

    m_resetButton = new QPushButton("Reset", this);
    connect(m_resetButton, &QPushButton::clicked, this, &ProgressRing::onResetButtonClicked);

    m_progressLabel = new QLabel("0%", this);
    m_progressLabel->setAlignment(Qt::AlignCenter);

    // Make label bigger and clearer
    QFont font = m_progressLabel->font();
    font.setPointSize(24);
    font.setBold(true);
    m_progressLabel->setFont(font);
    m_progressLabel->setStyleSheet("color: rgb(100, 100, 100); font-weight: bold;");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_startButton);
    buttonLayout->addWidget(m_stopButton);
    buttonLayout->addWidget(m_resetButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(1); // Add space above
    mainLayout->addWidget(m_progressLabel);
    mainLayout->addStretch(1); // Add space between label and buttons
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(0); // Minimal space at bottom

    setLayout(mainLayout);
    setFixedSize(400, 450); // Fixed window size
    setWindowTitle("Progress Ring Demo");
}

ProgressRing::~ProgressRing()
{
    delete m_timer;
    delete m_animation;
    delete m_startButton;
    delete m_stopButton;
    delete m_resetButton;
    delete m_progressLabel;
}

void ProgressRing::setProgress(int value)
{
    if (m_progress != value) {
        m_progress = value;
        m_progressLabel->setText(QString::number(m_progress) + "%");

        // Update label color to match progress ring
        QColor labelColor;
        if (m_progress < 50) {
            labelColor = QColor::fromHsv(0 + (60 * m_progress / 50), 200, 200);
        } else {
            labelColor = QColor::fromHsv(60 + (60 * (m_progress - 50) / 50), 200, 200);
        }
        m_progressLabel->setStyleSheet(QString("color: rgb(%1, %2, %3); font-weight: bold;")
                                      .arg(labelColor.red())
                                      .arg(labelColor.green())
                                      .arg(labelColor.blue()));

        update();
    }
}

void ProgressRing::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    // Center the ring in the upper portion, leaving space for buttons
    int ringSize = qMin(side, 300); // Limit ring size
    int xOffset = (width() - ringSize) / 2;
    int yOffset = 50; // Move ring up to make room for buttons
    painter.setViewport(xOffset, yOffset, ringSize, ringSize);
    painter.setWindow(-100, -100, 200, 200);

    // Draw background circle
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(220, 220, 220));
    painter.drawEllipse(-90, -90, 180, 180);

    // Calculate color based on progress
    QColor progressColor;
    if (m_progress < 50) {
        progressColor = QColor::fromHsv(0 + (60 * m_progress / 50), 200, 250);
    } else {
        progressColor = QColor::fromHsv(60 + (60 * (m_progress - 50) / 50), 200, 250);
    }

    // Draw progress arc with rounded caps
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(progressColor, 15, Qt::SolidLine, Qt::RoundCap));
    int angleSpan = static_cast<int>(360.0 * m_progress / 100.0 * 16);
    painter.drawArc(-90, -90, 180, 180, 90 * 16, -angleSpan);
}

void ProgressRing::onTimeout()
{
    if (m_targetProgress < 100)
    {
        m_targetProgress += 5;
        m_animation->setStartValue(m_progress);
        m_animation->setEndValue(m_targetProgress);
        m_animation->start();
    }
    else
    {
        m_timer->stop();
    }
}

void ProgressRing::onStartButtonClicked()
{
    if (!m_timer->isActive())
    {
        m_timer->start(500); // Update every 500 ms for smoother animation
    }
}

void ProgressRing::onStopButtonClicked()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
}

void ProgressRing::onResetButtonClicked()
{
    m_timer->stop();
    m_animation->stop();
    m_targetProgress = 0;
    m_animation->setStartValue(m_progress);
    m_animation->setEndValue(0);
    m_animation->setDuration(1000);
    m_animation->start();
}
