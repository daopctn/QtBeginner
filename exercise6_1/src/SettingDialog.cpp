
// settingsdialog.cpp
#include "SettingDialog.h"
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), settings("MyCompany", "MyApp")
{
    setupUi();
    loadSettings();
}

void SettingsDialog::setupUi()
{
    setWindowTitle("Settings");
    setMinimumSize(400, 300);

    auto *mainLayout = new QVBoxLayout(this);

    tabWidget = new QTabWidget(this);

    // General Tab
    auto *generalTab = new QWidget();
    auto *generalLayout = new QFormLayout(generalTab);

    usernameEdit = new QLineEdit();
    autoSaveCheck = new QCheckBox("Enable auto-save");
    intervalSpin = new QSpinBox();
    intervalSpin->setRange(1, 60);
    intervalSpin->setSuffix(" min");

    generalLayout->addRow("Username:", usernameEdit);
    generalLayout->addRow(autoSaveCheck);
    generalLayout->addRow("Save interval:", intervalSpin);

    tabWidget->addTab(generalTab, "General");

    // Appearance Tab
    auto *appearanceTab = new QWidget();
    auto *appearanceLayout = new QFormLayout(appearanceTab);

    themeCombo = new QComboBox();
    themeCombo->addItems({"Light", "Dark", "Auto"});

    fontSizeSpin = new QSpinBox();
    fontSizeSpin->setRange(8, 24);
    fontSizeSpin->setSuffix(" pt");

    showToolbarCheck = new QCheckBox("Show toolbar");

    appearanceLayout->addRow("Theme:", themeCombo);
    appearanceLayout->addRow("Font size:", fontSizeSpin);
    appearanceLayout->addRow(showToolbarCheck);

    tabWidget->addTab(appearanceTab, "Appearance");

    // Advanced Tab
    auto *advancedTab = new QWidget();
    auto *advancedLayout = new QFormLayout(advancedTab);

    debugCheck = new QCheckBox("Debug mode");
    proxyEdit = new QLineEdit();
    proxyEdit->setPlaceholderText("proxy.example.com:8080");

    cacheSpin = new QSpinBox();
    cacheSpin->setRange(10, 1000);
    cacheSpin->setSuffix(" MB");

    advancedLayout->addRow(debugCheck);
    advancedLayout->addRow("Proxy:", proxyEdit);
    advancedLayout->addRow("Cache size:", cacheSpin);

    tabWidget->addTab(advancedTab, "Advanced");

    // Buttons
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                           QDialogButtonBox::Cancel |
                                           QDialogButtonBox::Apply);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::onOk);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked,
            this, &SettingsDialog::onApply);

    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
}

void SettingsDialog::loadSettings()
{
    // General
    usernameEdit->setText(settings.value("General/Username", "").toString());
    autoSaveCheck->setChecked(settings.value("General/AutoSave", true).toBool());
    intervalSpin->setValue(settings.value("General/Interval", 10).toInt());

    // Appearance
    themeCombo->setCurrentIndex(settings.value("Appearance/Theme", 0).toInt());
    fontSizeSpin->setValue(settings.value("Appearance/FontSize", 12).toInt());
    showToolbarCheck->setChecked(settings.value("Appearance/ShowToolbar", true).toBool());

    // Advanced
    debugCheck->setChecked(settings.value("Advanced/Debug", false).toBool());
    proxyEdit->setText(settings.value("Advanced/Proxy", "").toString());
    cacheSpin->setValue(settings.value("Advanced/Cache", 100).toInt());
}

void SettingsDialog::saveSettings()
{
    // General
    settings.setValue("General/Username", usernameEdit->text());
    settings.setValue("General/AutoSave", autoSaveCheck->isChecked());
    settings.setValue("General/Interval", intervalSpin->value());

    // Appearance
    settings.setValue("Appearance/Theme", themeCombo->currentIndex());
    settings.setValue("Appearance/FontSize", fontSizeSpin->value());
    settings.setValue("Appearance/ShowToolbar", showToolbarCheck->isChecked());

    // Advanced
    settings.setValue("Advanced/Debug", debugCheck->isChecked());
    settings.setValue("Advanced/Proxy", proxyEdit->text());
    settings.setValue("Advanced/Cache", cacheSpin->value());
}

void SettingsDialog::onOk()
{
    saveSettings();
    accept();
}

void SettingsDialog::onApply()
{
    saveSettings();
}