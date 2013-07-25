#ifndef PAINTER_H
#define PAINTER_H

#include "interface/mainwindow.h"
#include "document.h"

class Painter
{
public:
    Painter(MainWindow *window);
    void paintWebpage(Document *webpage);

private:
    MainWindow *mainWindow;

};

#endif // PAINTER_H
