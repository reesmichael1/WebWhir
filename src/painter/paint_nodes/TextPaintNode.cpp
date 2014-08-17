#include "TextPaintNode.h"
#include "painter/wwPainter/wwpainter.h"

TextPaintNode::TextPaintNode(std::string textToSet)
{
    text = textToSet;
    xCoordinateOfEdgeOfLastLine = 0;
    QStringList lineList;
}

void TextPaintNode::paint(WWPainter *wwPainter, PaintArea *display, Layout *layout)
{
    calculateDimensions(display);
    layout->addPaintNode(this);
    QFont oldFont = wwPainter->font();
    wwPainter->setFont(createFontForNode(wwPainter));
    drawLines(wwPainter);
    /*
    wwPainter->drawInlineText(getCoordinates().x(), getCoordinates().y(),
                        getWidth(), getHeight(),
                        //Qt::TextWordWrap,
                       QString::fromStdString(text));
                       */
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

    splitTextIntoLinesForDisplay(display, &wwPainter);

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

int TextPaintNode::getXCoordinateOfEdgeOfLastLine()
{
    return xCoordinateOfEdgeOfLastLine;
}

void TextPaintNode::splitTextIntoLinesForDisplay(PaintArea *display, WWPainter *wwPainter)
{
    QStringList wordList = QString::fromStdString(text).split(" ");
    int currentWidth = 0;
    int maximumWidth = display->width();
    QString nextLine;
    QFontMetrics fm(createFontForNode(wwPainter));
    for (int i = 0; i < wordList.length(); i++)
    {
        QString nextWord = wordList.at(i);
        QRect nextWordBoundingRect = fm.tightBoundingRect(nextWord);
        if (currentWidth + nextWordBoundingRect.width() > maximumWidth)
        {
            lineList.append(nextLine);
            nextLine = nextWord;
            currentWidth = 0;
        }
        else
        {
            nextLine += nextWord;
            currentWidth += nextWordBoundingRect.width();
        }
    }
    if (!nextLine.isEmpty())
    {
        lineList.append(nextLine);
    }
}

void TextPaintNode::drawLines(WWPainter *wwPainter)
{
    int currentY = 0;
    int lineHeight = 20; // compute this
    for (int i = 0; i < lineList.length(); i++)
    {
        wwPainter->drawText(0, currentY, lineList.at(i));
        currentY += lineHeight;
    }
}
