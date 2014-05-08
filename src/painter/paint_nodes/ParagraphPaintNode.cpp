#include <QPainter>

#include "ParagraphPaintNode.h"

ParagraphPaintNode::ParagraphPaintNode()
{
    text = "";
}

void ParagraphPaintNode::setText(std::string textToSet)
{
    text = textToSet;
}

std::string ParagraphPaintNode::getText()
{
    return text;
}

void ParagraphPaintNode::paint(QPainter *qPainter, PaintArea *display)
{
    QRect textDimensions(0, 0, 100, 100);
    qPainter->drawText(display->geometry(), Qt::TextWordWrap,
                       QString::fromStdString(text), &textDimensions);

    paintChildNodes(qPainter, display);
}
