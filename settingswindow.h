#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QSqlTableModel>
#include <valarray>

#include "databasecontroller.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(DatabaseController* controller, QWidget *parent = nullptr);
    ~SettingsWindow();

    void update_list();
    int get_id();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    DatabaseController *controller;
    QSqlTableModel *model;
    int plane_id = 1;

    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
