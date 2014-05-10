#include "TextPaintNode.h"
#include <QPainter>

TextPaintNode::TextPaintNode(std::string textToSet)
{
    text = textToSet;
}

void TextPaintNode::paint(QPainter *qPainter, PaintArea *display)
{
    QRect textDimensions(0, 0, 100, 100);
    qPainter->drawText(display->geometry(), Qt::TextWordWrap,
                       QString::fromStdString(text), &textDimensions);

    //A TextPaintNode should never have child nodes,
    //so there's no need to paint them.
}
