#include "authwindow.h"
#include "databasehelper.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthWindow w;

    DataBase database;
    database.connectToDataBase();

    w.show();
    return a.exec();
}
