#include <QApplication> // Provides the QApplication class for managing application-wide resources
// This application demonstrates a simple drag-and-drop interface using two QListWidgets.
// Users can drag items between the lists and edit them by double-clicking.
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
#include <QListWidget>
#include <QAbstractItemView>

// Main window class for the Mouse Tracker
// Main window class for the drag-and-drop text exercise
class Exercise43Window : public QWidget
{
    Q_OBJECT

public:
    // Constructor: sets up the UI and connects signals/slots
    Exercise43Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 4.3: Drag and Drop Text"); // Set window title
        centerWindow();                                     // Center the window on the screen
        setFixedSize(600, 400);                             // Set fixed window size

        // Create the main horizontal layout
        mainLayout = new QHBoxLayout(this);

        // Create the left list widget and add initial items
        leftList = new QListWidget(this);
        leftList->addItems({"Item 1", "Item 2", "Item 3", "Item 4", "Item 5"});

        // Make all items in the left list editable
        for (int i = 0; i < leftList->count(); ++i)
        {
            leftList->item(i)->setFlags(leftList->item(i)->flags() | Qt::ItemIsEditable);
        }

        mainLayout->addWidget(leftList); // Add left list to layout

        // Create the right list widget
        rightList = new QListWidget(this);
        mainLayout->addWidget(rightList); // Add right list to layout

        // Set selection mode to single selection for both lists
        leftList->setSelectionMode(QAbstractItemView::SingleSelection);
        rightList->setSelectionMode(QAbstractItemView::SingleSelection);

        // Allow editing items by double-clicking
        leftList->setEditTriggers(QAbstractItemView::DoubleClicked);
        rightList->setEditTriggers(QAbstractItemView::DoubleClicked);

        // Enable drag and drop for both lists
        leftList->setDragDropMode(QAbstractItemView::DragDrop);
        rightList->setDragDropMode(QAbstractItemView::DragDrop);
        leftList->setDefaultDropAction(Qt::MoveAction);
        rightList->setDefaultDropAction(Qt::MoveAction);
        leftList->setDragEnabled(true);
        rightList->setDragEnabled(true);
        leftList->setAcceptDrops(true);
        rightList->setAcceptDrops(true);

        // Ensure items remain editable after being pressed
        connect(leftList, &QListWidget::itemPressed, this, [this](QListWidgetItem *item)
                {
    if (item)
    {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } });

        connect(rightList, &QListWidget::itemPressed, this, [this](QListWidgetItem *item)
                {
    if (item)
    {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    } });
    }

private:
    // Helper function to center the window on the screen
    void centerWindow()
    {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();

        // Calculate coordinates to center the window
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;

        move(x, y);
    }

    QListWidget *leftList;
    QListWidget *rightList;
    QHBoxLayout *mainLayout;
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