#include <QApplication>
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

class Exercise33Window : public QWidget
{
    Q_OBJECT

public:
    Exercise33Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Exercise 3.3: Survey Form");
        centerWindow();
        setMinimumSize(600, 400);
        // Main layout
        mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(10);
        // Title label
        titleLabel = new QLabel("Survey Form", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-weight: bold; font-size: 16pt;");
        mainLayout->addWidget(titleLabel);

        // Form layout
        formLayout = new QHBoxLayout();
        mainLayout->addLayout(formLayout);

        // Name input
        formLayout->addWidget(new QLabel("Name:", this));
        formLayout->addWidget(nameLineEdit = new QLineEdit(this));
        // Age input
        formLayout->addWidget(new QLabel("Age:", this));
        formLayout->addWidget(ageSpinBox = new QSpinBox(this));
        ageSpinBox->setRange(0, 120);
        ageSpinBox->setValue(25);
        // Gender input
        formLayout->addWidget(new QLabel("Gender:", this));
        QHBoxLayout *genderLayout = new QHBoxLayout();
        genderLayout->addWidget(maleRadio = new QRadioButton("Male", this));
        genderLayout->addWidget(femaleRadio = new QRadioButton("Female", this));
        formLayout->addLayout(genderLayout);

        // Interests layout
        interestsLayout = new QGridLayout();
        mainLayout->addLayout(interestsLayout);
        interestsLayout->setSpacing(5);
        interestsLayout->addWidget(interestsCheckBox1 = new QCheckBox("Sports", this), 0, 0);
        interestsLayout->addWidget(interestsCheckBox2 = new QCheckBox("Music", this), 0, 1);
        interestsLayout->addWidget(interestsCheckBox3 = new QCheckBox("Travel", this), 1, 0);
        interestsLayout->addWidget(interestsCheckBox4 = new QCheckBox("Reading", this), 1, 1);
        interestsLayout->addWidget(interestsCheckBox5 = new QCheckBox("Gaming", this), 2, 0);
        interestsLayout->setColumnStretch(2, 1);
        interestsLayout->setRowStretch(3, 1);

        // Comments input
        mainLayout->addWidget(new QLabel("Comments:", this));
        mainLayout->addWidget(commentsTextEdit = new QTextEdit(this));
        commentsTextEdit->setPlaceholderText("Enter your comments here...");

        // Submit button
        submitButton = new QPushButton("Submit", this);
        mainLayout->addWidget(submitButton);
        submitButton->setFixedWidth(100);
        submitButton->setStyleSheet("font-weight: bold;");
        submitButton->setCursor(Qt::PointingHandCursor);
        submitButton->setDefault(true);
        mainLayout->setAlignment(submitButton, Qt::AlignHCenter);
        connect(submitButton, &QPushButton::clicked, this, &Exercise33Window::submitForm);
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

    void submitForm()
    {
        QString name = nameLineEdit->text().trimmed();
        int age = ageSpinBox->value();
        QString gender = maleRadio->isChecked() ? "Male" : "Female";
        QStringList interests;
        if (interestsCheckBox1->isChecked())
            interests << "Sports";
        if (interestsCheckBox2->isChecked())
            interests << "Music";
        if (interestsCheckBox3->isChecked())
            interests << "Travel";
        if (interestsCheckBox4->isChecked())
            interests << "Reading";
        if (interestsCheckBox5->isChecked())
            interests << "Gaming";
        QString comments = commentsTextEdit->toPlainText();
        // Display collected data in a message box
        QString result = QString("Name: %1\nAge: %2\nGender: %3\nInterests: %4\nComments: %5")
                             .arg(name.isEmpty() ? "N/A" : name)
                             .arg(age)
                             .arg(gender)
                             .arg(interests.isEmpty() ? "N/A" : interests.join(", "))
                             .arg(comments.isEmpty() ? "N/A" : comments);

        QMessageBox::information(this, "Survey Result", result, QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    }

    QLabel *titleLabel;
    QLineEdit *nameLineEdit;
    QSpinBox *ageSpinBox;
    QRadioButton *maleRadio;
    QRadioButton *femaleRadio;
    QCheckBox *interestsCheckBox1;
    QCheckBox *interestsCheckBox2;
    QCheckBox *interestsCheckBox3;
    QCheckBox *interestsCheckBox4;
    QCheckBox *interestsCheckBox5;
    QTextEdit *commentsTextEdit;
    QPushButton *submitButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *formLayout;
    QGridLayout *interestsLayout;
    QMessageBox *messageBox;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Exercise33Window window;
    window.show();
    return app.exec();
}

#include "main.moc"