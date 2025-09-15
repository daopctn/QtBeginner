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
#include <QDoubleSpinBox>
#include <QRadioButton>

class Exercise32Window : public QWidget
{
    Q_OBJECT

public:
    Exercise32Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Temperature Converter - Exercise 3.2");
        setMinimumSize(600, 400);
        centerWindow();

        // Main layout
        mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(10);

        // Title label
        titleLabel = new QLabel("Temperature Converter", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-weight: bold; font-size: 16pt;");
        // add Titlelabel to mainLayout
        mainLayout->addWidget(titleLabel);

        // Input layout
        inputLayout = new QHBoxLayout();
        inputLayout->addWidget(inputCelsiusRadio = new QRadioButton("Celsius", this));
        inputLayout->addWidget(inputFahrenheitRadio = new QRadioButton("Fahrenheit", this));
        inputLayout->addWidget(inputKelvinRadio = new QRadioButton("Kelvin", this));
        inputCelsiusRadio->setChecked(true);
        inputLayout->setAlignment(Qt::AlignHCenter);
        // add inputLayout to mainLayout
        mainLayout->addLayout(inputLayout);

        // Temperature layout
        temperatureLayout = new QGridLayout();
        temperatureLayout->addWidget(inputTemperatureSpinBox = new QDoubleSpinBox(this), 0, 1);
        inputTemperatureSpinBox->setRange(-273.15, 1000.0);
        inputTemperatureSpinBox->setValue(0.0);
        temperatureLayout->addWidget(new QLabel("Celsius:", this), 1, 0);
        temperatureLayout->addWidget(outputCelsiusLabel = new QLabel("0.00 °C", this), 1, 1);
        temperatureLayout->addWidget(new QLabel("Fahrenheit:", this), 2, 0);
        temperatureLayout->addWidget(outputFahrenheitLabel = new QLabel("32.00 °F", this), 2, 1);
        temperatureLayout->addWidget(new QLabel("Kelvin:", this), 3, 0);
        temperatureLayout->addWidget(outputKelvinLabel = new QLabel("273.15 K", this), 3, 1); // add temperatureLayout to mainLayout
        mainLayout->addLayout(temperatureLayout);

        // connect buttons and spinbox to updateTemperatures function
        // update values when spinbox value changes or radio button toggled
        connect(inputTemperatureSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Exercise32Window::updateTemperatures);
        connect(inputCelsiusRadio, &QRadioButton::toggled, this, &Exercise32Window::updateTemperatures);
        connect(inputFahrenheitRadio, &QRadioButton::toggled, this, &Exercise32Window::updateTemperatures);
        connect(inputKelvinRadio, &QRadioButton::toggled, this, &Exercise32Window::updateTemperatures);

        setLayout(mainLayout);

        // initial update of temperature values, maybe dont need this
        updateTemperatures();
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

    void updateTemperatures()
    {
        double inputTemp = inputTemperatureSpinBox->value();
        double celsius, fahrenheit, kelvin;

        if (inputCelsiusRadio->isChecked())
        {
            celsius = inputTemp;
            fahrenheit = celsius * 9.0 / 5.0 + 32.0;
            kelvin = celsius + 273.15;
        }
        else if (inputFahrenheitRadio->isChecked())
        {
            fahrenheit = inputTemp;
            celsius = (fahrenheit - 32.0) * 5.0 / 9.0;
            kelvin = celsius + 273.15;
        }
        else
        { // Kelvin
            kelvin = inputTemp;
            celsius = kelvin - 273.15;
            fahrenheit = celsius * 9.0 / 5.0 + 32.0;
        }

        outputCelsiusLabel->setText(QString::number(celsius, 'f', 2) + " °C");
        outputFahrenheitLabel->setText(QString::number(fahrenheit, 'f', 2) + " °F");
        outputKelvinLabel->setText(QString::number(kelvin, 'f', 2) + " K");
    }

    QLabel *titleLabel;
    QDoubleSpinBox *inputTemperatureSpinBox;
    QRadioButton *inputCelsiusRadio;
    QRadioButton *inputFahrenheitRadio;
    QRadioButton *inputKelvinRadio;
    QLabel *outputCelsiusLabel;
    QLabel *outputFahrenheitLabel;
    QLabel *outputKelvinLabel;
    QVBoxLayout *mainLayout;
    QHBoxLayout *inputLayout;
    QGridLayout *temperatureLayout;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Exercise32Window window;
    window.show();
    return app.exec();
}

#include "main.moc"