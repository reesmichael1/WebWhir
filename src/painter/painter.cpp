#include "painter.h"

#include <QPainter>

Painter::Painter(MainWindow *window)
{
    mainWindow = window;
}

void Painter::addCharacter(const char c, QFont::Weight weight)
{
    mainWindow->addCharacter(QString(c), weight);
}
