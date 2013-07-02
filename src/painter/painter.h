#ifndef PAINTER_H
#define PAINTER_H

#include "interface/mainwindow.h"
#include "document.h"

class Painter
{
public:
    Painter(MainWindow *window);
    //void addCharacter(const char c);
    void addCharacter(const char c, QFont::Weight weight = QFont::Bold);
    void paintWebpage(Document *webpage);

private:
    MainWindow *mainWindow;

};

#endif // PAINTER_H
