#include "databasewindow.h"
#include "./ui_databasewindow.h"

DatabaseWindow::DatabaseWindow(DatabaseController* controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DatabaseWindow)
{
    this -> controller = controller;
    ui -> setupUi(this);

    QStringList list = (this -> controller -> db.tables(QSql::Tables));
    list.removeAll ("sqlite_sequence");

    ui -> dbTableNameComboBox -> addItems(list);
}

DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}

void DatabaseWindow::on_dbTableNameComboBox_currentIndexChanged(const QString &arg1)
{
    tableModel = new QSqlTableModel(this);

    tableModel -> setTable(ui->dbTableNameComboBox->currentText());
    tableModel -> select();
    ui -> dbTableView -> setModel(tableModel);
}

void DatabaseWindow::on_dbAddRow_clicked()
{
    tableModel -> insertRow (tableModel -> rowCount());
}

void DatabaseWindow::on_dbRemoveRow_clicked()
{
    tableModel -> removeRow(currentRow);
    tableModel -> select();
}


void DatabaseWindow::on_dbTableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}
