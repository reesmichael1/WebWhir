#ifndef PAINTER_H
#define PAINTER_H

#include "interface/mainwindow.h"

class Painter
{
public:
    Painter();
    void setWindowToPaint(MainWindow *window);
    void paint();

private:
    MainWindow *mainWindow;

};

#endif // PAINTER_H
