
// settingsdialog.h
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

QT_BEGIN_NAMESPACE
class QTabWidget;
class QCheckBox;
class QSpinBox;
class QComboBox;
class QLineEdit;
QT_END_NAMESPACE

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private slots:
    void onOk();
    void onApply();

private:
    void setupUi();
    void loadSettings();
    void saveSettings();

    QTabWidget *tabWidget;
    QSettings settings;

    // General Tab
    QLineEdit *usernameEdit;
    QCheckBox *autoSaveCheck;
    QSpinBox *intervalSpin;

    // Appearance Tab
    QComboBox *themeCombo;
    QSpinBox *fontSizeSpin;
    QCheckBox *showToolbarCheck;

    // Advanced Tab
    QCheckBox *debugCheck;
    QLineEdit *proxyEdit;
    QSpinBox *cacheSpin;
};

#endif