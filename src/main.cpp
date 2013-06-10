#include <iostream>
#include <string>
#include <fstream>

#include <QApplication>

#include "interface/mainwindow.h"

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    MainWindow mainWindow;

    if (argc > 1)
    {
        mainWindow.setFilepath(argv[1]);
    }

    else
    {
        mainWindow.setFilepath();
    }

    mainWindow.paintDocument();
    mainWindow.show();

    return app.exec();
}
