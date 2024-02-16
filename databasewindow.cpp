#include "databasewindow.h"
#include "./ui_databasewindow.h"

DatabaseWindow::DatabaseWindow(DatabaseController* controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DatabaseWindow)
{
    this -> controller = controller;
    ui->setupUi(this);

    QStringList list=(this -> controller -> db.tables(QSql::Tables));
    ui->tableNameComboBox->addItems(list);
}

DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}


void DatabaseWindow::on_tableNameComboBox_currentIndexChanged(const QString &arg1)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(this -> controller -> db);

    qry->prepare("select * from " + ui->tableNameComboBox->currentText());

    qry->exec();

    model->setQuery(*qry);
    ui->tablesView->setModel(model);

    qDebug() << (model->rowCount());
}
