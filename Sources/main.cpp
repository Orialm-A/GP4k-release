#include "Headers/mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Creating the application...

    MainWindow w; // Creating the window...

    w.show(); // Showing the window...

    return a.exec();
}
