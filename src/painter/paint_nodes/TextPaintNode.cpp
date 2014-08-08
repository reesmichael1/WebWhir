#include "TextPaintNode.h"
#include "painter/wwPainter/wwpainter.h"

TextPaintNode::TextPaintNode(std::string textToSet)
{
    text = textToSet;
}

void TextPaintNode::paint(WWPainter *wwPainter, PaintArea *display, Layout *layout)
{
    calculateDimensions(display);
    layout->addPaintNode(this);
    QFont oldFont = wwPainter->font();
    wwPainter->setFont(createFontForNode(wwPainter));
    wwPainter->drawInlineText(getCoordinates().x(), getCoordinates().y(),
                        getWidth(), getHeight(),
                        //Qt::TextWordWrap,
                       QString::fromStdString(text));
    wwPainter->setFont(oldFont);

    //A TextPaintNode should never have child nodes,
    //so there's no need to paint them.
}

void TextPaintNode::calculateDimensions(PaintArea *display)
{
    WWPainter wwPainter(display);
    wwPainter.setFont(createFontForNode(&wwPainter));
    QSize size = wwPainter.boundingRect(display->geometry(),
            QString::fromStdString(text)).size().toSize();

    dimensions = size;
}

QFont TextPaintNode::createFontForNode(WWPainter *wwPainter)
{
    QFont currentFont = wwPainter->font();
    if (std::find(this->getPaintOptions().begin(),
                  this->getPaintOptions().end(), boldText) !=
            this->getPaintOptions().end())
    {
        currentFont.setBold(true);
    }

    return currentFont;
}
