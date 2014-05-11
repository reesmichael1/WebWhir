#include "TextPaintNode.h"
#include <QPainter>

TextPaintNode::TextPaintNode(std::string textToSet)
{
    text = textToSet;
}

void TextPaintNode::paint(QPainter *qPainter, PaintArea *display, Layout *layout)
{
    calculateDimensions(display);
    layout->addPaintNode(this);
    qPainter->drawText(getCoordinates().x(), getCoordinates().y(),
                       getWidth(), getHeight(), Qt::TextWordWrap,
                       QString::fromStdString(text));

    //A TextPaintNode should never have child nodes,
    //so there's no need to paint them.
}

void TextPaintNode::calculateDimensions(PaintArea *display)
{
    QPainter qPainter(display);
    QSize size = qPainter.boundingRect(display->geometry(),
            QString::fromStdString(text)).size().toSize();

    dimensions = size;
}
