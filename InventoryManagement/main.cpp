
#include "GUI/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.setWindowTitle("Inventory Mangement");
    w.show();
    return a.exec();
}
