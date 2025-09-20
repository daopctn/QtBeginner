// main.cpp
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include "SettingDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QWidget window;
    auto *layout = new QVBoxLayout(&window);
    
    auto *button = new QPushButton("Open Settings");
    layout->addWidget(button);
    
    QObject::connect(button, &QPushButton::clicked, [&]() {
        SettingsDialog dialog(&window);
        dialog.exec();
    });
    
    window.setWindowTitle("Settings Example");
    window.show();
    
    return app.exec();
}