#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlTableModel>
#include <valarray>

#include "databasecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DatabaseWindow; }
QT_END_NAMESPACE

class DatabaseWindow : public QMainWindow
{
    Q_OBJECT

private:
    DatabaseController *controller;
    QSqlTableModel *tableModel;
    int currentRow;

public:
    DatabaseWindow(DatabaseController* controller, QWidget *parent = nullptr);
    ~DatabaseWindow();

private slots:


    void on_dbTableNameComboBox_currentIndexChanged(const QString &arg1);

    void on_dbAddRow_clicked();

    void on_dbRemoveRow_clicked();

    void on_dbTableView_clicked(const QModelIndex &index);

private:
    Ui::DatabaseWindow *ui;
};
#endif // DATABASEWINDOW_H
