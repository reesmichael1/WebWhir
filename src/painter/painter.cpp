#include "painter.h"

Painter::Painter()
{
    mainWindow = new MainWindow;
}

void Painter::setWindowToPaint(MainWindow *window)
{
    mainWindow = window;
}

void Painter::paint()
{
    std::string *webpageString;
    mainWindow->getWebpage()->paintWebpage(webpageString);

    mainWindow->setMainText(webpageString);
}
