#include <iostream>
#include <string>
#include <fstream>

#include <QApplication>

#include "interface/mainwindow.h"

int main(int argc, char* argv[])
{

    //Define the base window.
    QApplication app(argc, argv);
    MainWindow mainWindow;

    //Open the document if passed via the command line.
    if (argc > 1)
    {
        mainWindow.setFilepath(argv[1]);

        //Display the painted document.
        mainWindow.show();
    }

    //Otherwise, show the "Open HTML Document" dialog.
    else
    {
        if (mainWindow.setFilepath())
        {
            mainWindow.show();
        }
    }

    return app.exec();
}
