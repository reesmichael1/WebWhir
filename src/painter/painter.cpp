#include "painter.h"

#include <QPainter>

Painter::Painter(MainWindow *window)
{
    mainWindow = window;
}

void Painter::addCharacter(const char c)
{
    mainWindow->addCharacter(QString(c));
}

void Painter::paintWebpage(Document *webpage)
{
    webpage->getFirstNode()->paintNode();
}


