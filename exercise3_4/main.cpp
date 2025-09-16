#include <QApplication> // Provides the QApplication class for managing application-wide resources
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
#include <QSpinBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QComboBox>

// Main window class for the pizza order form
class Exercise34Window : public QWidget
{
    Q_OBJECT

public:
    // Constructor: sets up the UI and connects signals/slots
    Exercise34Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 3.4: Pizza Order Form"); // Set window title
        centerWindow();                                   // Center the window on the screen
        setMinimumSize(600, 400);                         // Set minimum window size

        // Main vertical layout for the window
        mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(10);

        // Title label at the top
        titleLabel = new QLabel("Pizza Order Form", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-weight: bold; font-size: 16pt;");
        mainLayout->addWidget(titleLabel);

        // Name input field
        nameLineEdit = new QLineEdit(this);
        nameLineEdit->setPlaceholderText("Enter your name");
        mainLayout->addWidget(new QLabel("Name:", this));
        mainLayout->addWidget(nameLineEdit);

        // Pizza size selection dropdown
        sizeComboBox = new QComboBox(this);
        sizeComboBox->addItems({"Small", "Medium", "Large", "Extra Large"});
        mainLayout->addWidget(new QLabel("Pizza Size:", this));
        mainLayout->addWidget(sizeComboBox);

        // Toppings selection using checkboxes in a grid layout
        toppingLayout = new QGridLayout();
        toppingLayout->addWidget(topping1CheckBox = new QCheckBox("Pepperoni", this), 0, 0);
        toppingLayout->addWidget(topping2CheckBox = new QCheckBox("Mushrooms", this), 0, 1);
        toppingLayout->addWidget(topping3CheckBox = new QCheckBox("Onions", this), 0, 2);
        toppingLayout->addWidget(topping4CheckBox = new QCheckBox("Sausage", this), 1, 0);
        toppingLayout->addWidget(topping5CheckBox = new QCheckBox("Bacon", this), 1, 1);
        toppingLayout->addWidget(topping6CheckBox = new QCheckBox("Extra cheese", this), 1, 2);
        toppingLayout->addWidget(topping7CheckBox = new QCheckBox("Black olives", this), 2, 0);
        toppingLayout->addWidget(topping8CheckBox = new QCheckBox("Green peppers", this), 2, 1);
        toppingLayout->addWidget(topping9CheckBox = new QCheckBox("Pineapple", this), 2, 2);
        mainLayout->addWidget(new QLabel("Toppings:", this));
        mainLayout->addLayout(toppingLayout);
        // Delivery or Pickup selection using radio buttons
        deliveryLayout = new QGridLayout();
        deliveryLayout->addWidget(deliveryRadio = new QRadioButton("Delivery", this), 0, 0);
        deliveryLayout->addWidget(pickupRadio = new QRadioButton("Pickup", this), 0, 1);
        deliveryRadio->setChecked(true); // Default to Delivery
        mainLayout->addWidget(new QLabel("Order Type:", this));
        mainLayout->addLayout(deliveryLayout);

        // Address input for delivery
        addressTextEdit = new QTextEdit(this);
        addressTextEdit->setPlaceholderText("Enter your address for delivery");
        mainLayout->addWidget(new QLabel("Address (for delivery):", this));
        mainLayout->addWidget(addressTextEdit);

        // Price display label
        priceLabel = new QLabel("Total Price: $0.00", this);
        priceLabel->setAlignment(Qt::AlignCenter);
        priceLabel->setStyleSheet("font-weight: bold; font-size: 14pt;");
        mainLayout->addWidget(priceLabel);

        // Submit order button
        submitButton = new QPushButton("Submit Order", this);
        mainLayout->addWidget(submitButton);
        mainLayout->setAlignment(submitButton, Qt::AlignHCenter);
        submitButton->setFixedWidth(120);
        submitButton->setStyleSheet("font-weight: bold;");
        submitButton->setCursor(Qt::PointingHandCursor);
        submitButton->setDefault(true);

        // Connect signals to update price and handle submission
        connect(sizeComboBox, &QComboBox::currentTextChanged, this, &Exercise34Window::updatePrice);
        connect(topping1CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping2CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping3CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping4CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping5CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping6CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping7CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping8CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(topping9CheckBox, &QCheckBox::stateChanged, this, &Exercise34Window::updatePrice);
        connect(submitButton, &QPushButton::clicked, this, &Exercise34Window::summitMessage);
        updatePrice(); // Initialize price
    }

private:
    // Helper function to center the window on the screen
    void centerWindow()
    {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();

        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;

        move(x, y);
    }
    // Calculate and update the total price based on size and toppings
    void updatePrice()
    {
        double basePrice = 10.0; // Base price for small pizza
        QString size = sizeComboBox->currentText();
        // Adjust base price based on pizza size
        if (size == "Medium")
            basePrice += 2.0;
        else if (size == "Large")
            basePrice += 4.0;
        else if (size == "Extra Large")
            basePrice += 6.0;

        // Count selected toppings
        int toppingCount = 0;
        if (topping1CheckBox->isChecked())
            toppingCount++;
        if (topping2CheckBox->isChecked())
            toppingCount++;
        if (topping3CheckBox->isChecked())
            toppingCount++;
        if (topping4CheckBox->isChecked())
            toppingCount++;
        if (topping5CheckBox->isChecked())
            toppingCount++;
        if (topping6CheckBox->isChecked())
            toppingCount++;
        if (topping7CheckBox->isChecked())
            toppingCount++;
        if (topping8CheckBox->isChecked())
            toppingCount++;
        if (topping9CheckBox->isChecked())
            toppingCount++;

        double toppingsPrice = toppingCount * 1.5; // Each topping costs $1.5
        double totalPrice = basePrice + toppingsPrice;

        // Update the price label
        priceLabel->setText(QString("Total Price: $%1").arg(totalPrice, 0, 'f', 2));
    }

    // Show a summary message box when the order is submitted
    void summitMessage()
    {
        QString name = nameLineEdit->text().trimmed();
        // Validate name input
        if (name.isEmpty())
        {
            QMessageBox::warning(this, "Input Error", "Please enter your name.");
            return;
        }

        QString size = sizeComboBox->currentText();
        // Collect selected toppings
        QStringList toppings;
        if (topping1CheckBox->isChecked())
            toppings << "Pepperoni";
        if (topping2CheckBox->isChecked())
            toppings << "Mushrooms";
        if (topping3CheckBox->isChecked())
            toppings << "Onions";
        if (topping4CheckBox->isChecked())
            toppings << "Sausage";
        if (topping5CheckBox->isChecked())
            toppings << "Bacon";
        if (topping6CheckBox->isChecked())
            toppings << "Extra cheese";
        if (topping7CheckBox->isChecked())
            toppings << "Black olives";
        if (topping8CheckBox->isChecked())
            toppings << "Green peppers";
        if (topping9CheckBox->isChecked())
            toppings << "Pineapple";

        QString orderType = deliveryRadio->isChecked() ? "Delivery" : "Pickup";
        QString address = addressTextEdit->toPlainText().trimmed();
        // If delivery is selected, address is required
        if (deliveryRadio->isChecked() && address.isEmpty())
        {
            QMessageBox::warning(this, "Input Error", "Please enter your address for delivery.");
            return;
        }

        // Build order summary string
        QString summary = QString("Order Summary:\n\nName: %1\nSize: %2\nToppings: %3\nOrder Type: %4")
                              .arg(name)
                              .arg(size)
                              .arg(toppings.isEmpty() ? "None" : toppings.join(", "))
                              .arg(orderType);
        if (deliveryRadio->isChecked())
        {
            summary += QString("\nAddress: %1").arg(address);
        }
        summary += QString("\n%1").arg(priceLabel->text());

        // Show the summary in a message box
        QMessageBox::information(this, "Order Submitted", summary);
    }

    QLabel *titleLabel;
    QLineEdit *nameLineEdit;
    QComboBox *sizeComboBox;
    QCheckBox *topping1CheckBox;
    QCheckBox *topping2CheckBox;
    QCheckBox *topping3CheckBox;
    QCheckBox *topping4CheckBox;
    QCheckBox *topping5CheckBox;
    QCheckBox *topping6CheckBox;
    QCheckBox *topping7CheckBox;
    QCheckBox *topping8CheckBox;
    QCheckBox *topping9CheckBox;
    QRadioButton *deliveryRadio;
    QRadioButton *pickupRadio;
    QTextEdit *addressTextEdit;
    QLabel *priceLabel;
    QPushButton *submitButton;
    QVBoxLayout *mainLayout;
    QGridLayout *toppingLayout;
    QGridLayout *deliveryLayout;
};

// Main function: entry point of the application
int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create application object
    Exercise34Window window;      // Create main window
    window.show();                // Show the window
    return app.exec();            // Enter the Qt event loop
}

#include "main.moc"