#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include "databasecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DatabaseWindow; }
QT_END_NAMESPACE

class DatabaseWindow : public QMainWindow
{
    Q_OBJECT

private:
    DatabaseController* controller;

public:
    DatabaseWindow(DatabaseController* controller, QWidget *parent = nullptr);
    ~DatabaseWindow();

private slots:


    void on_tableNameComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::DatabaseWindow *ui;
};
#endif // DATABASEWINDOW_H
