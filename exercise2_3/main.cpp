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

class Exercise23Window : public QWidget
{
    Q_OBJECT

public:
    Exercise23Window(QWidget *parent = nullptr)
    {
        QLabel *titleLabel = new QLabel("Simple Calculator", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont titleFont = titleLabel->font();
        titleFont.setPointSize(16);
        titleFont.setBold(true);
        titleLabel->setFont(titleFont);
        resize(300, 400);
        centerWindow();
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(titleLabel);
        screen = new QTextEdit(this);
        screen->setReadOnly(true);
        screen->setMaximumHeight(80);
        screen->setMinimumHeight(80);
        QFont screenFont = screen->font();
        screenFont.setPointSize(24);
        screen->setFont(screenFont);
        screen->setAlignment(Qt::AlignRight);
        mainLayout->addWidget(screen);

        QGridLayout *buttonLayout = new QGridLayout();

        for (int i = 0; i < 10; ++i) {
            numButton[i] = new QPushButton(QString::number(i), this);
            connect(numButton[i], &QPushButton::clicked, this, [this, i]() {
                screen->insertPlainText(QString::number(i));
            });
        }

        buttonLayout->addWidget(numButton[7], 0, 0);
        buttonLayout->addWidget(numButton[8], 0, 1);
        buttonLayout->addWidget(numButton[9], 0, 2);
        buttonLayout->addWidget(numButton[4], 1, 0);
        buttonLayout->addWidget(numButton[5], 1, 1);
        buttonLayout->addWidget(numButton[6], 1, 2);
        buttonLayout->addWidget(numButton[1], 2, 0);
        buttonLayout->addWidget(numButton[2], 2, 1);
        buttonLayout->addWidget(numButton[3], 2, 2);
        buttonLayout->addWidget(numButton[0], 3, 1);

        addButton = new QPushButton("+", this);
        subButton = new QPushButton("-", this);
        mulButton = new QPushButton("*", this);
        divButton = new QPushButton("/", this);
        eqButton = new QPushButton("=", this);
        clearButton = new QPushButton("C", this);
        exitButton = new QPushButton("Exit", this);

        buttonLayout->addWidget(addButton, 0, 3);
        buttonLayout->addWidget(subButton, 1, 3);
        buttonLayout->addWidget(mulButton, 2, 3);
        buttonLayout->addWidget(divButton, 3, 3);
        buttonLayout->addWidget(eqButton, 3, 2);
        buttonLayout->addWidget(clearButton, 3, 0);

        mainLayout->addLayout(buttonLayout);
        mainLayout->addWidget(exitButton);
        connect(addButton, &QPushButton::clicked, this, [this]() {
            screen->insertPlainText("+");
        });
        connect(subButton, &QPushButton::clicked, this, [this]() {
            screen->insertPlainText("-");
        });
        connect(mulButton, &QPushButton::clicked, this, [this]() {
            screen->insertPlainText("*");
        });
        connect(divButton, &QPushButton::clicked, this, [this]() {
            screen->insertPlainText("/");
        });
        // connect(eqButton, &QPushButton::clicked, this, [this]() {
        //     QString expression = screen->toPlainText();
        //     // Simple evaluation logic (for demonstration purposes only)
        //     // In a real application, consider using a proper expression parser
        //     double result = 0;
        //     QChar op;
        //     QStringList tokens = expression.split(QRegExp("([+\\-*/])"), Qt::SkipEmptyParts);
        //     if (tokens.size() < 2) return; // Not enough tokens to evaluate
        //     result = tokens[0].toDouble();
        //     for (int i = 1; i < tokens.size(); i += 2) {
        //         op = expression.at(expression.indexOf(tokens[i - 1]) + tokens[i - 1].length());
        //         double nextValue = tokens[i].toDouble();
        //         if (op == '+') result += nextValue;
        //         else if (op == '-') result -= nextValue;
        //         else if (op == '*') result *= nextValue;
        //         else if (op == '/') {
        //             if (nextValue != 0) result /= nextValue;
        //             else {
        //                 QMessageBox::warning(this, "Error", "Division by zero");
        //                 return;
        //             }
        //         }
        //     }
        //     screen->setPlainText(QString::number(result));
        // });
        connect(clearButton, &QPushButton::clicked, this, [this]() {
            screen->clear();
        });
        connect(exitButton, &QPushButton::clicked, this, [this]() {
            qApp->quit();
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

    QLabel *titleLabel;
    QTextEdit *screen;
    QPushButton *numButton[10];
    QPushButton *addButton;
    QPushButton *subButton;
    QPushButton *mulButton;
    QPushButton *divButton;
    QPushButton *eqButton;
    QPushButton *clearButton;
    QPushButton *exitButton;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Exercise23Window window;
    window.show();

    return app.exec();
}

#include "main.moc"
