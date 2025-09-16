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
#include <QMouseEvent>
#include <QShortcut>
// Main window class for the Mouse Tracker
class Exercise42Window : public QWidget
{
    Q_OBJECT

public:
    // Constructor: sets up the UI and connects signals/slots
    Exercise42Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 4.2: Keyboard Shortcuts");                         // Set window title
        centerWindow();                                                             // Center the window on the screen
        setFixedSize(400, 300);                                                     // Set fixed window size
        mainLayout = new QVBoxLayout(this);                                         // Create main vertical layout
        titleLabel = new QLabel("Keyboard Shortcuts Demo", this);                   // Create title label
        titleLabel->setAlignment(Qt::AlignCenter);                                  // Center-align the title label
        titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");           // Style the title label
        mainLayout->addWidget(titleLabel);                                          // Add title label to layout
        textEdit = new QTextEdit(this);                                             // Create text edit field
        textEdit->setPlaceholderText("Type here...");                               // Set placeholder text
        mainLayout->addWidget(textEdit);                                            // Add text edit to layout
        lastPressedShortcutLabel = new QLabel("Last pressed shortcut: None", this); // Create label for last pressed shortcut
        mainLayout->addWidget(lastPressedShortcutLabel);                            // Add label to layout

        // Create shortcuts
        QShortcut *quitShortcut = new QShortcut(QKeySequence("Ctrl+Q"), this);
        connect(quitShortcut, &QShortcut::activated, this, &QWidget::close);
        QShortcut *helpShortcut = new QShortcut(QKeySequence("Ctrl+H"), this);
        connect(helpShortcut, &QShortcut::activated, this, &Exercise42Window::showHelpMessage);

        QShortcut *clearShortcut = new QShortcut(QKeySequence("Ctrl+N"), this);
        // label change on shortcut pressed
        connect(clearShortcut, &QShortcut::activated, this, [this]()
                {
            lastPressedShortcutLabel->setText("Last pressed shortcut: Ctrl+N");
            textEdit->clear(); });
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
    void showHelpMessage()
    {
        QMessageBox::information(this, "Help", "This application demonstrates keyboard shortcuts:\n\n"
                                               "Ctrl+Q: Quit the application\n"
                                               "Ctrl+H: Show this help message");
        lastPressedShortcutLabel->setText("Last pressed shortcut: Ctrl+H");
    }
    QVBoxLayout *mainLayout;          // Main layout for the window
    QLabel *titleLabel;               // Title label
    QTextEdit *textEdit;              // Text edit field
    QLabel *lastPressedShortcutLabel; // Label to display last pressed shortcut
};

// Main function: entry point of the application
int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create application object
    Exercise42Window window;      // Create main window
    window.show();                // Show the window
    return app.exec();            // Enter the Qt event loop
}

#include "main.moc"