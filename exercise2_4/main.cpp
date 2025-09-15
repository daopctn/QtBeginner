#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QFont>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

class Exercise24Window : public QWidget
{
    Q_OBJECT

public:
    Exercise24Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Contact Card");
        centerWindow();
        mainLayout = new QVBoxLayout(this);
        topLayout = new QHBoxLayout();
        titleLabel = new QLabel("Contact Card", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(titleLabel);
        imageHolderLabel = new QLabel(this);
        imageHolderLabel->setFixedSize(100, 100);
        imageHolderLabel->setStyleSheet("background-color: lightgray; border: 1px solid black;");
        topLayout->addWidget(imageHolderLabel);
        infoLayout = new QVBoxLayout();
        nameLabel = new QLabel("Name: John Doe", this);
        phoneLabel = new QLabel("Phone: (123) 456-7890", this);
        emailLabel = new QLabel("Email: daopctn@gmail.com", this);
        infoLayout->addWidget(nameLabel);
        infoLayout->addWidget(phoneLabel);
        infoLayout->addWidget(emailLabel);
        topLayout->addLayout(infoLayout);
        mainLayout->addLayout(topLayout);
        buttonLayout = new QHBoxLayout();
        editButton = new QPushButton("Edit", this);
        exitButton = new QPushButton("Exit", this);
        buttonLayout->addWidget(editButton);
        buttonLayout->addWidget(exitButton);
        mainLayout->addLayout(buttonLayout);

    }

private:
    void centerWindow()
    {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();

        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;

        move(x, y);
    }
    QVBoxLayout *mainLayout;
    QVBoxLayout *infoLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *topLayout;
    QLabel *titleLabel;
    QLabel *imageHolderLabel;
    QLabel *nameLabel;
    QLabel *phoneLabel;
    QLabel *emailLabel;
    QPushButton *editButton;
    QPushButton *exitButton;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Exercise24Window window;
    window.show();
    return app.exec();
}

#include "main.moc"
