#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QColor>
#include <QSlider>
#include <QSpinBox>

class Exercise31Window : public QWidget
{
    Q_OBJECT

public:
    Exercise31Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Color Mixer - Exercise 3.1");
        setMinimumSize(600, 400);
        centerWindow();
        mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(10);
        colorDisplay = new QLabel(this);
        colorDisplay->setFixedHeight(100);
        colorDisplay->setFixedWidth(200);
        colorDisplay->setStyleSheet("background-color: rgb(0, 0, 0); border: 1px solid black;");
        mainLayout->addWidget(colorDisplay, 0, Qt::AlignHCenter);
        hexaRGBLabel = new QLabel("Hexa RGB: #000000", this);
        hexaRGBLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(hexaRGBLabel);

        redLayout = new QHBoxLayout();
        mainLayout->addLayout(redLayout);
        QLabel *redLabel = new QLabel("Red:", this);
        redLabel->setFixedWidth(50);
        redLayout->addWidget(redLabel);
        redSlider = new QSlider(Qt::Horizontal, this);
        redSlider->setRange(0, 255);
        redLayout->addWidget(redSlider);
        redSpinBox = new QSpinBox(this);
        redSpinBox->setRange(0, 255);
        redLayout->addWidget(redSpinBox);
        greenLayout = new QHBoxLayout();
        mainLayout->addLayout(greenLayout);
        QLabel *greenLabel = new QLabel("Green:", this);
        greenLabel->setFixedWidth(50);
        greenLayout->addWidget(greenLabel);
        greenSlider = new QSlider(Qt::Horizontal, this);
        greenSlider->setRange(0, 255);
        greenLayout->addWidget(greenSlider);
        greenSpinBox = new QSpinBox(this);
        greenSpinBox->setRange(0, 255);
        greenLayout->addWidget(greenSpinBox);
        blueLayout = new QHBoxLayout();
        mainLayout->addLayout(blueLayout);
        QLabel *blueLabel = new QLabel("Blue:", this);
        blueLabel->setFixedWidth(50);
        blueLayout->addWidget(blueLabel);
        blueSlider = new QSlider(Qt::Horizontal, this);
        blueSlider->setRange(0, 255);
        blueLayout->addWidget(blueSlider);
        blueSpinBox = new QSpinBox(this);
        blueSpinBox->setRange(0, 255);
        blueLayout->addWidget(blueSpinBox);
        connect(redSlider, &QSlider::valueChanged, this, &Exercise31Window::updateColorDisplay);
        connect(redSpinBox, &QSpinBox::editingFinished, this, [=]()
                { redSlider->setValue(redSpinBox->value()); });
        connect(greenSlider, &QSlider::valueChanged, this, &Exercise31Window::updateColorDisplay);
        connect(greenSpinBox, &QSpinBox::editingFinished, this, [=]()
                { greenSlider->setValue(greenSpinBox->value()); });
        connect(blueSlider, &QSlider::valueChanged, this, &Exercise31Window::updateColorDisplay);
        connect(blueSpinBox, &QSpinBox::editingFinished, this, [=]()
                { blueSlider->setValue(blueSpinBox->value()); });
        setLayout(mainLayout);
    }

private:
    void centerWindow()
    {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();

        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;

        move(x, y);
    }
    void updateColorDisplay()
    {
        int r = redSlider->value();
        int g = greenSlider->value();
        int b = blueSlider->value();
        QString style = QString("background-color: rgb(%1, %2, %3); border: 1px solid black;").arg(r).arg(g).arg(b);
        colorDisplay->setStyleSheet(style);
        QString hexa = QString("#%1%2%3")
                           .arg(r, 2, 16, QChar('0'))
                           .arg(g, 2, 16, QChar('0'))
                           .arg(b, 2, 16, QChar('0'))
                           .toUpper();
        hexaRGBLabel->setText("Hexa RGB: " + hexa);
        redSpinBox->setValue(r);
        greenSpinBox->setValue(g);
        blueSpinBox->setValue(b);
    }
    QVBoxLayout *mainLayout;
    QLabel *colorDisplay;
    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;
    QSpinBox *redSpinBox;
    QSpinBox *greenSpinBox;
    QSpinBox *blueSpinBox;
    QHBoxLayout *redLayout;
    QHBoxLayout *greenLayout;
    QHBoxLayout *blueLayout;
    QLabel *hexaRGBLabel;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Exercise31Window window;
    window.show();
    return app.exec();
}

#include "main.moc"