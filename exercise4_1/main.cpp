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

// Main window class for the Mouse Tracker
class Exercise41Window : public QWidget
{
    Q_OBJECT

public:
    // Constructor: sets up the UI and connects signals/slots
    Exercise41Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 4.1: Mouse Tracker"); // Set window title

        centerWindow();                                  // Center the window on the screen
        setFixedSize(400, 300);                          // Set fixed window size
        QVBoxLayout *mainLayout = new QVBoxLayout(this); // Main vertical layout
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(10);
        // Title label at the top
        QLabel *titleLabel = new QLabel("Mouse Tracker", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);
        // Coordinate display label
        coordinateLabel = new QLabel("Coordinates: (0, 0)", this);
        mainLayout->addWidget(coordinateLabel);
        // Status display label
        statusLabel = new QLabel("Status: Released", this);
        mainLayout->addWidget(statusLabel);
        // Distance display label
        distanceLabel = new QLabel("Total Distance: 0 px", this);
        mainLayout->addWidget(distanceLabel);
        // Inside/outside display label
        insideLabel = new QLabel("Mouse Outside", this);
        mainLayout->addWidget(insideLabel);
        setMouseTracking(true); // Enable mouse tracking
        updateStatus();         // Initialize status display
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

    // Override mouse event handlers to track mouse movements
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            isPressing = true;
            lastPosition = event->pos();
            setStyleSheet("background-color: lightblue;"); // on press
            totalDistance = 0.0;
            updateStatus();
        }
    }
    void enterEvent(QEnterEvent *event) override
    {
        insideLabel->setText("Mouse Inside");
    }
    void leaveEvent(QEvent *event) override
    {
        insideLabel->setText("Mouse Outside");
    }
    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (isPressing)
        {
            QPoint currentPosition = event->pos();
            double distance = std::hypot(currentPosition.x() - lastPosition.x(),
                                         currentPosition.y() - lastPosition.y());
            totalDistance += distance;
            lastPosition = currentPosition;
            updateStatus();
        }
    }
    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            isPressing = false;
            updateStatus();
            setStyleSheet("background-color: lightgray;"); // on release
        }
    }
    void updateStatus()
    {
        if (isPressing)
        {
            statusLabel->setText("Mouse Pressed");
        }
        else
        {
            statusLabel->setText("Mouse Released");
        }
        coordinateLabel->setText(QString("Coordinates: (%1, %2)")
                                     .arg(lastPosition.x())
                                     .arg(lastPosition.y()));
        distanceLabel->setText(QString("Total Distance: %1 px").arg(totalDistance, 0, 'f', 2));
    }
    // UI components
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;

    QLabel *coordinateLabel;
    QLabel *statusLabel;
    QLabel *distanceLabel;
    QLabel *insideLabel;

    QPoint lastPosition;
    double totalDistance = 0.0;
    bool isPressing = false;
};

// Main function: entry point of the application
int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create application object
    Exercise41Window window;      // Create main window
    window.show();                // Show the window
    return app.exec();            // Enter the Qt event loop
}

#include "main.moc"