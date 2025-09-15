#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>
#include <QVBoxLayout>
#include <QMessageBox>

class Exercise2Window : public QWidget
{
    Q_OBJECT

public:
    Exercise2Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 2: Basic GUI with Qt");
        resize(400, 200);
        centerWindow();
        QVBoxLayout *layout = new QVBoxLayout(this);
        titleLabel = new QLabel("Welcome to Exercise 2", this);
        
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        layout->addWidget(titleLabel);
        inputField = new QTextEdit(this);
        inputField->setPlaceholderText("Enter some text here");
        layout->addWidget(inputField);
        saveButton = new QPushButton("Save", this);
        clearButton = new QPushButton("Clear", this);
        exitButton = new QPushButton("Exit", this);
        layout->addWidget(saveButton);
        layout->addWidget(clearButton);
        layout->addWidget(exitButton);
        connect(saveButton, &QPushButton::clicked, this, [this]() {
            QString text = inputField->toPlainText();
            if (!text.isEmpty()) {
                QMessageBox::information(this, "Saved", "Text saved: " + text);
            } else {
                QMessageBox::warning(this, "Warning", "Input field is empty!");
            }
        });

        connect(clearButton, &QPushButton::clicked, this, [this]() {
            inputField->clear();
        });

        connect(exitButton, &QPushButton::clicked, this, [this]() {
            showMessageBox();
        });
    }

private:
    void centerWindow()
    {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();

        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;

        move(x, y);
    };

    void showMessageBox()
    {
        // quit message box
        msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Quit");
        msgBox->setText("Are you sure you want to quit?");
        msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox->setDefaultButton(QMessageBox::No);
        int ret = msgBox->exec();
        if (ret == QMessageBox::Yes)
        {
            qApp->quit();
        }
    }

    QLabel *titleLabel;
    QTextEdit *inputField;
    QPushButton *saveButton;
    QPushButton *clearButton;
    QPushButton *exitButton;
    QMessageBox *msgBox;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Exercise2Window window;
    window.show();

    return app.exec();
}

#include "main.moc"
