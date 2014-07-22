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
    QFont oldFont = qPainter->font();
    qPainter->setFont(createFontForNode(qPainter));
    qPainter->drawText(getCoordinates().x(), getCoordinates().y(),
                       getWidth(), getHeight(), Qt::TextWordWrap,
                       QString::fromStdString(text));
    qPainter->setFont(oldFont);

    //A TextPaintNode should never have child nodes,
    //so there's no need to paint them.
}

void TextPaintNode::calculateDimensions(PaintArea *display)
{
    QPainter qPainter(display);
    qPainter.setFont(createFontForNode(&qPainter));
    QSize size = qPainter.boundingRect(display->geometry(),
            QString::fromStdString(text)).size().toSize();

    dimensions = size;
}

QFont TextPaintNode::createFontForNode(QPainter *qPainter)
{
    QFont currentFont = qPainter->font();
    if (std::find(this->getPaintOptions().begin(),
                  this->getPaintOptions().end(), boldText) !=
            this->getPaintOptions().end())
    {
        currentFont.setBold(true);
    }

    return currentFont;
}
