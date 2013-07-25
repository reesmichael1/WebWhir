#include "painter.h"

#include <QPainter>

//Currently, this is a useless class. As part of the refactoring,
//I will make this a custom widget and set it as part of the layout
//in the main window. This means that I can set the paint event for
//the painter to match the paint event of the main window. Then, I
//will be able to set this widget as the widget of a scroll area,
//which should allow me to implement scrolling.

Painter::Painter(MainWindow *window)
{
    mainWindow = window;
}
