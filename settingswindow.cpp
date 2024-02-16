#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(DatabaseController* controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{    
    this -> controller = controller;
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    plane_id = arg1.split(".")[0].toInt();
}

void SettingsWindow::update_list()
{
    ui->comboBox->clear();
    auto vector_planes =(this -> controller -> findAircrafts());
    QStringList list_planes;
    for(auto plane : vector_planes)
        list_planes << QString::number(plane.id) + ". " + plane.name;

    ui->comboBox->addItems(list_planes);
}

int SettingsWindow::get_id()
{
    return plane_id;
}
