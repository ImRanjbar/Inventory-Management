
#include "mainwindow.h"
#include "datahandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataHandler data;
    Manufacturers* manufacturersData = new Manufacturers;
    data.readData(manufacturersData);

    MainWindow w(manufacturersData);
    w.show();
    return a.exec();
}
