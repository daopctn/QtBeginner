#ifndef PROGRESSRING_H
#define PROGRESSRING_H
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QEasingCurve>

class ProgressRing : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int progress READ progress WRITE setProgress)

public:
    explicit ProgressRing(QWidget *parent = nullptr);
    ~ProgressRing();

    int progress() const { return m_progress; }
    void setProgress(int value);

protected:
    void paintEvent(QPaintEvent *event) override;
    void onTimeout();
    void onStartButtonClicked();
    void onStopButtonClicked();
    void onResetButtonClicked();

private:
    int m_progress;
    int m_targetProgress;
    QTimer *m_timer;
    QPropertyAnimation *m_animation;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QPushButton *m_resetButton;
    QLabel *m_progressLabel;
};

#endif // PROGRESSRING_H