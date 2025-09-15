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

class Exercise22Window : public QWidget
{
    Q_OBJECT

public:
    Exercise22Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 2.2: Login Form");
        resize(300, 150);
        centerWindow();
        QVBoxLayout *layout = new QVBoxLayout(this);

        usernameLabel = new QLabel("Username:", this);
        layout->addWidget(usernameLabel);
        usernameInput = new QLineEdit(this);
        layout->addWidget(usernameInput);

        passwordLabel = new QLabel("Password:", this);
        layout->addWidget(passwordLabel);
        passwordInput = new QLineEdit(this);
        passwordInput->setEchoMode(QLineEdit::Password);
        layout->addWidget(passwordInput);

        loginButton = new QPushButton("Login", this);
        cancelButton = new QPushButton("Cancel", this);
        layout->addWidget(loginButton);
        layout->addWidget(cancelButton);

        connect(loginButton, &QPushButton::clicked, this, [this]() {
            QString username = usernameInput->text();
            QString password = passwordInput->text();
            if (username == "admin" && password == "password") {
                QMessageBox::information(this, "Login Successful", "Welcome, " + username + "!");
            } else {
                QMessageBox::critical(this, "Login Failed", "Invalid username or password.");
            }
        });

        connect(cancelButton, &QPushButton::clicked, this, [this]() {
            usernameInput->clear();
            passwordInput->clear();
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

    QLabel *usernameLabel;
    QLineEdit *usernameInput;
    QLabel *passwordLabel;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *cancelButton;

};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Exercise22Window window;
    window.show();

    return app.exec();
}

#include "main.moc"
