#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

class Exercise25Window : public QWidget
{
    Q_OBJECT

public:
    Exercise25Window(QWidget *parent = nullptr)
    {
        setWindowTitle("Dynamic Layout - Exercise 2.5");
        setMinimumSize(400, 300);
        centerWindow();
        setupUI();
    }

private slots:
    void addField()
    {
        // Create a new horizontal layout for this field
        QHBoxLayout *fieldLayout = new QHBoxLayout();

        // Create line edit and remove button
        QLineEdit *lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText("Enter text here...");

        QPushButton *removeBtn = new QPushButton("Remove", this);
        removeBtn->setMaximumWidth(80);

        // Add widgets to field layout
        fieldLayout->addWidget(lineEdit);
        fieldLayout->addWidget(removeBtn);

        // Connect remove button - lambda captures all needed references
        connect(removeBtn, &QPushButton::clicked, [this, fieldLayout, lineEdit, removeBtn]() {
            // Remove widgets from layout
            fieldLayout->removeWidget(lineEdit);
            fieldLayout->removeWidget(removeBtn);

            // Delete widgets
            lineEdit->deleteLater();
            removeBtn->deleteLater();

            // Remove layout from parent and delete it
            fieldsLayout->removeItem(fieldLayout);
            delete fieldLayout;
        });

        // Add field layout to the fields container
        fieldsLayout->addLayout(fieldLayout);
    }

private:
    void setupUI()
    {
        // Main layout
        mainLayout = new QVBoxLayout(this);

        // Title label
        titleLabel = new QLabel("Dynamic Input Fields", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");
        mainLayout->addWidget(titleLabel);

        // Add Field button
        addButton = new QPushButton("Add Field", this);
        connect(addButton, &QPushButton::clicked, this, &Exercise25Window::addField);
        mainLayout->addWidget(addButton);

        // Scroll area for dynamic fields
        scrollArea = new QScrollArea(this);
        scrollWidget = new QWidget();
        fieldsLayout = new QVBoxLayout(scrollWidget);
        fieldsLayout->setAlignment(Qt::AlignTop);

        scrollArea->setWidget(scrollWidget);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        mainLayout->addWidget(scrollArea);
    }

    void centerWindow()
    {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();

        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;

        move(x, y);
    }

    // UI Components - NO TRACKING VECTORS NEEDED
    QVBoxLayout *mainLayout;
    QVBoxLayout *fieldsLayout;
    QLabel *titleLabel;
    QPushButton *addButton;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Exercise25Window window;
    window.show();
    return app.exec();
}

#include "main.moc"