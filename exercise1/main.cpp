#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

class Exercise1Window : public QWidget
{
    Q_OBJECT

public:
    Exercise1Window(QWidget *parent = nullptr)
    {
        counter = 0; // initialize variable
        setWindowTitle("Click window");
        // setFixedSize(400, 300);

        label = new QLabel(this);
        label->setText("Clicks: 0");
        label->setStyleSheet("font-size: 16pt;");

        label->setAlignment(Qt::AlignCenter);
        label1 = new QLabel(this);
        label1->setStyleSheet("font-size: 16pt;");

        label1->setAlignment(Qt::AlignCenter);

        button = new QPushButton("Click me", this);

        lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText("Type here");
        lineEdit->setMaxLength(50);
        
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(button);
        layout->addWidget(label1);
        layout->addWidget(lineEdit);
        setLayout(layout);

        quitButton = new QPushButton("Quit", this);
        layout->addWidget(quitButton);
        layout->setAlignment(quitButton, Qt::AlignRight);
        connect(quitButton, &QPushButton::clicked, this, &Exercise1Window::showMessageBox);

        connect(lineEdit, &QLineEdit::textChanged, this, &Exercise1Window::updateText);
        connect(button, &QPushButton::clicked, this, &Exercise1Window::updateValue);
        centerWindow();
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
    void updateValue()
    {
        counter++;                                          // change variable
        label->setText(QString("Clicks: %1").arg(counter)); // update QLabel
    }
    void updateText(const QString &text)
    {
        label1->setText(text); // update QLabel
    }

    void showMessageBox()
    {
        //quit message box
        msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Quit");
        msgBox->setText("Are you sure you want to quit?");
        msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox->setDefaultButton(QMessageBox::No);
        int ret = msgBox->exec();
        if (ret == QMessageBox::Yes) {
            qApp->quit();
        }   
    }

    QLabel *label;
    QLabel *label1;
    QPushButton *button;
    int counter;
    QLineEdit *lineEdit;
    QVBoxLayout *layout;
    QMessageBox *msgBox;
    QPushButton *quitButton;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Exercise1Window window;
    window.show();

    return app.exec();
}

#include "main.moc"
