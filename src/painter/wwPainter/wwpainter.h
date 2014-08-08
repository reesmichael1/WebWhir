#ifndef WWPAINTER_H
#define WWPAINTER_H

#include <QPainter>

class WWPainter : public QPainter
{
public:
    WWPainter(QPaintDevice *parent = 0);
    void drawInlineText(int xOffset, int y, int width, int height, QString text);
};

#endif // WWPAINTER_H
