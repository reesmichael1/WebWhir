#include <iostream>
#include "TextPaintNode.h"
#include "painter/wwPainter/wwpainter.h"

QHash<QString, int> wordHash;
int lineHeight = 15;

// This is just here as a prototype of what I'm trying to do with the reflow
// My long term goal is to subclass QFont and add the same functionality
void populateCharacterHash(QHash<QString, int> &characterHash)
{
    QString alphabet = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ.,?!\\-/:;\'\"";
    QFont font = QFont();
    QFontMetrics fm(font);
    for (int i = 0; i < alphabet.length(); i++)
    {
        characterHash.insert(alphabet.at(i), fm.width(alphabet.at(i)));
    }

}

int getWidthOfString(QHash<QString, int> characterHash, QString string)
{
    if (wordHash.contains(string))
    {
        return wordHash.value(string);
    }
    int width = 0;
    for (int i = 0; i < string.length(); i++)
    {
        width += characterHash.value(string.at(i));
    }

    wordHash.insert(string, width);
    return width;
}

TextPaintNode::TextPaintNode(std::string textToSet)
{
    text = textToSet;
    isInline = true;
    populateCharacterHash(characterHash);
}

TextPaintNode::~TextPaintNode()
{
    delete fm;
}

void TextPaintNode::paint(WWPainter &wwPainter, PaintArea *display, Layout *layout)
{
    layout->addPaintNode(this, display);
    WWPainter newPainter(display);
    QFont oldFont = newPainter.font();
    newPainter.setFont(createFontForNode(newPainter));
    drawLines(&newPainter, display);
    newPainter.setFont(oldFont);

    //A TextPaintNode should never have child nodes,
    //so there's no need to paint them.
}

void TextPaintNode::calculateDimensions(PaintArea *display)
{
    WWPainter wwPainter(display);
    wwPainter.setFont(createFontForNode(wwPainter));
    QSize size = wwPainter.boundingRect(display->geometry(),
            QString::fromStdString(text)).size().toSize();

    splitTextIntoLinesForDisplay(display, wwPainter);

    dimensions.setHeight(lineHeight * lineList.size());
    dimensions.setWidth(size.width());
}

QFont TextPaintNode::createFontForNode(WWPainter &wwPainter)
{
    QFont currentFont = wwPainter.font();
    if (std::find(this->getPaintOptions().begin(),
                  this->getPaintOptions().end(), boldText) !=
            this->getPaintOptions().end())
    {
        currentFont.setBold(true);
    }

    fm = new QFontMetrics(currentFont);

    return currentFont;
}

QFont TextPaintNode::createFontForNode()
{
    QFont currentFont;

    if (std::find(this->getPaintOptions().begin(),
                  this->getPaintOptions().end(), boldText) !=
            this->getPaintOptions().end())
    {
        currentFont.setBold(true);
    }

    return currentFont;
}

void TextPaintNode::splitTextIntoLinesForDisplay(PaintArea *display, WWPainter &wwPainter)
{
    lineList.clear();
    QStringList wordList = QString::fromStdString(text).split(" ", QString::SkipEmptyParts);
    int currentWidth = xCoordinateOfStartOfFirstLine;
    int maximumWidth = display->width();
    QString nextLine;
    for (int i = 0; i < wordList.length(); i++)
    {
        QString nextWord = (wordList.at(i) + " ");
        int nextWordWidth = getWidthOfString(characterHash, nextWord);
        if (currentWidth + nextWordWidth > maximumWidth)
        {
            lineList.append(nextLine);
            nextLine = nextWord;
            currentWidth = 0;
        }
        else
        {
            nextLine += nextWord;
            currentWidth += nextWordWidth;
        }
    }
    if (!nextLine.isEmpty())
    {
        lineList.append(nextLine);
    }
    xCoordinateOfEdgeOfLastLine = currentWidth;
}

bool TextPaintNode::regionContainsPaintNode(const QRegion &region)
{
    return (region.contains(QPoint(coordinates.x(), coordinates.y() + dimensions.height())) ||
            region.contains(QPoint(coordinates.x(), coordinates.y() - dimensions.height())));
}

void TextPaintNode::drawLines(WWPainter *wwPainter, PaintArea *display)
{
    /*
    if (this->regionContainsPaintNode(display->visibleRegion()))
    {
    */
        int currentY = coordinates.y();
        int verticalPadding = 5;
        for (int i = 0; i < lineList.length(); i++)
        {
            int currentX;
            if (i == 0)
            {
                currentX = xCoordinateOfStartOfFirstLine;
            }
            else
            {
                currentX = 0;
            }

            wwPainter->drawText(QRect(currentX, currentY, wwPainter->device()->width(), lineHeight),
                                lineList.at(i));
            currentY += (lineHeight + verticalPadding);
        }
    //}
}

QSize TextPaintNode::getDimensions(PaintArea *display)
{
    calculateDimensions(display);
    return dimensions;
}
