#include <QApplication> // Provides the QApplication class for managing application-wide resources
// This application demonstrates a simple drag-and-drop interface using two QListWidgets.
// Users can drag items between the lists and edit them by double-clicking.
#include <QScreen>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QMessageBox>
#include <QShortcut>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

class FindDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindDialog(QTextEdit *editor, QWidget *parent = nullptr)
        : QDialog(parent), textEdit(editor)
    {
        setWindowTitle("Find");
        QHBoxLayout *layout = new QHBoxLayout(this);
        lineEdit = new QLineEdit(this);
        QPushButton *findButton = new QPushButton("Find", this);

        layout->addWidget(lineEdit);
        layout->addWidget(findButton);

        connect(findButton, &QPushButton::clicked, this, &FindDialog::onFindClicked);
    }

private slots:
    void onFindClicked()
    {
        QString searchText = lineEdit->text();
        if (!searchText.isEmpty())
        {
            if (!textEdit->find(searchText))
            {
                // Restart search from beginning if not found
                textEdit->moveCursor(QTextCursor::Start);
                textEdit->find(searchText);
            }
        }
    }

private:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
};

class Exercise45Window : public QWidget
{
    Q_OBJECT

public:
    // Constructor: sets up the UI and connects signals/slots
    Exercise45Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 4.5: Custom Context Menu"); // Set window title
        centerWindow();                                      // Center the window on the screen
        setFixedSize(600, 400);                              // Set fixed window size

        // Create the main vertical layout
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        wordCountLabel = new QLabel("Word Count: 0", this);
        charCountLabel = new QLabel("Character Count: 0", this);
        textEdit = new QTextEdit(this);
        mainLayout->addWidget(wordCountLabel);
        mainLayout->addWidget(charCountLabel);
        mainLayout->addWidget(textEdit);

        // Create the custom context menu
        QMenu *contextMenu = new QMenu(this);
        QAction *clearAction = contextMenu->addAction("Clear Text");
        QAction *copyAction = contextMenu->addAction("Copy Text");
        QAction *pasteAction = contextMenu->addAction("Paste Text");
        QAction *selectAllAction = contextMenu->addAction("Select All");
        // Set up the text edit with the custom context menu
        textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(textEdit, &QTextEdit::customContextMenuRequested, this, [this, contextMenu](const QPoint &pos)
                { contextMenu->exec(textEdit->mapToGlobal(pos)); });
        connect(textEdit, &QTextEdit::textChanged, this, &Exercise45Window::updateCounts);
        connect(clearAction, &QAction::triggered, textEdit, &QTextEdit::clear);
        connect(copyAction, &QAction::triggered, textEdit, &QTextEdit::copy);
        connect(pasteAction, &QAction::triggered, textEdit, &QTextEdit::paste);
        connect(selectAllAction, &QAction::triggered, textEdit, &QTextEdit::selectAll);

        // Create and connect the Find dialog
        QShortcut *findShortcut = new QShortcut(QKeySequence("Ctrl+F"), this);
        findDialog = new FindDialog(textEdit, this);
        connect(findShortcut, &QShortcut::activated, findDialog, &FindDialog::show);

        updateCounts(); // Initialize word and
    }

private slots:
    // Slot to update word and character counts
    void updateCounts()
    {
        QString text = textEdit->toPlainText();
        int wordCount = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).count();
        int charCount = text.length();
        wordCountLabel->setText(QString("Word Count: %1").arg(wordCount));
        charCountLabel->setText(QString("Character Count: %1").arg(charCount));
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
    QLabel *wordCountLabel;
    QLabel *charCountLabel;
    QTextEdit *textEdit;
    FindDialog *findDialog;
};

// Main function: entry point of the application
int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create application object
    Exercise45Window window;      // Create main window
    window.show();                // Show the window
    return app.exec();            // Enter the Qt event loop
}

#include "main.moc"