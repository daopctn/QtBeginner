#include <QApplication> // Provides the QApplication class for managing application-wide resources
// This application creates a simple password strength checker GUI using Qt.
// Users can enter a password and see if it meets common security criteria.
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
#include <QProgressBar>
#include <QRegularExpression>

// Main window class for the password strength checker
class Exercise35Window : public QWidget
{
    Q_OBJECT

public:
    // Constructor: sets up the UI and connects signals/slots
    Exercise35Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 3.5: Password Strength Checker"); // Set window title
        centerWindow();                                            // Center the window on the screen
        setFixedSize(400, 300);                                    // Set fixed window size

        // Main vertical layout for the window
        mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(10);

        // Title label at the top
        titleLabel = new QLabel("Password Strength Checker", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);

        // Password input field
        passwordLineEdit = new QLineEdit(this);
        passwordLineEdit->setEchoMode(QLineEdit::Password); // Hide password text
        passwordLineEdit->setPlaceholderText("Enter your password");
        mainLayout->addWidget(passwordLineEdit);

        // Progress bar to show password strength
        strengthProgressBar = new QProgressBar(this);
        strengthProgressBar->setRange(0, 100);
        strengthProgressBar->setValue(0);
        mainLayout->addWidget(strengthProgressBar);

        // Label to display which criteria are met or not
        criteriaLabel = new QLabel(this);
        mainLayout->addWidget(criteriaLabel);

        // Connect password input changes to the criteria checking function
        connect(passwordLineEdit, &QLineEdit::textChanged, this, &Exercise35Window::checkCriteria);
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
    };

    // Checks the password against common security criteria and updates the UI
    void checkCriteria()
    {
        // Retrieve the entered password
        QString password = passwordLineEdit->text();
        // Start with all criteria met, subtract for each unmet
        QString criteriaNoti = "Criteria not met:";
        int criteriaMet = 5;

        // Check for minimum length
        if (password.length() < 8)
        {
            criteriaNoti += "\n At least 8 characters";
            criteriaMet--;
        }
        // Check for at least one uppercase letter
        if (!password.contains(QRegularExpression("[A-Z]")))
        {
            criteriaNoti += "\n Contains uppercase letters";
            criteriaMet--;
        }
        // Check for at least one lowercase letter
        if (!password.contains(QRegularExpression("[a-z]")))
        {
            criteriaNoti += "\n Contains lowercase letters";
            criteriaMet--;
        }
        // Check for at least one digit
        if (!password.contains(QRegularExpression("[0-9]")))
        {
            criteriaNoti += "\n Contains numbers";
            criteriaMet--;
        }
        // Check for at least one special character
        if (!password.contains(QRegularExpression("[^a-zA-Z0-9]")))
        {
            criteriaNoti += "\n Contains special characters";
            criteriaMet--;
        }

        // If all criteria are met, update the notification
        if (criteriaMet == 5)
        {
            criteriaNoti = "All criteria met!";
        }
        // Update the label and progress bar
        criteriaLabel->setText(criteriaNoti);
        strengthProgressBar->setValue(criteriaMet * 20);
    };

    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLineEdit *passwordLineEdit;
    QProgressBar *strengthProgressBar;
    QLabel *criteriaLabel;
};

// Main function: entry point of the application
int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create application object
    Exercise35Window window;      // Create main window
    window.show();                // Show the window
    return app.exec();            // Enter the Qt event loop
}

#include "main.moc"