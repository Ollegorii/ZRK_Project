#include "databasewindow.h"
#include <iostream>

#include <QApplication>
#include "databasecontroller.h"
#include "models.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseController controller ("../ZRK115_DB/zrkdb.sqlite");

    DatabaseWindow w (&controller);
    w.show();
    return a.exec();
}
