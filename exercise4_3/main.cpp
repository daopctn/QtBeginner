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
class Exercise43Window : public QWidget
{
    Q_OBJECT

public:
    // Constructor: sets up the UI and connects signals/slots
    Exercise43Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 4.3: Drag and Drop Text"); // Set window title
        centerWindow();                                     // Center the window on the screen
        setFixedSize(400, 300);                             // Set fixed window size
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
};

// Main function: entry point of the application
int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create application object
    Exercise43Window window;      // Create main window
    window.show();                // Show the window
    return app.exec();            // Enter the Qt event loop
}

#include "main.moc"