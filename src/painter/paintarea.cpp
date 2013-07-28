#include "paintarea.h"

#define STARTING_X 10

//Padding from the right side of the window
#define RIGHT_SIDE_X 30
#define STARTING_Y 10

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    webpage = new Document;
    positionSet = false;

    currentCharacter = new QString;
}

void PaintArea::setDocument(Document *documentToSet)
{
    webpage = documentToSet;
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    //Draw the document (this will be split off into Painter soon).
    Q_UNUSED(event);

    if (webpage->getFirstNode() != NULL)
    {

        QPainter qPainter(this);
        paintNodesVector = webpage->getFirstNode()->getPaintNodes();
        drawDocument(&qPainter, paintNodesVector);

        //Prevents document from moving around while being redrawn.
        positionSet = true;

        //This is necessary to show the entire paint area in the scroll area.
        setMinimumHeight(currentY);
    }
}

void PaintArea::drawDocument(QPainter *qPainter,
                              std::vector<PaintNode*> *paintNodes)
{
    std::vector<PaintNode*>::iterator i = paintNodes->begin();

    for (; i != paintNodes->end(); i++)
    {
        paintCurrentNode(*i, qPainter);
    }
}

void PaintArea::insertLineBreak()
{
    QFont font = currentFont;
    QFontMetrics fm(font);

    currentX = STARTING_X;
    currentY += 2 * fm.height();
    totalWidth = 0;
}

void PaintArea::paintCurrentNode(PaintNode *currentPaintNode,
                                  QPainter *qPainter)
{
    if (currentPaintNode->getTypeOfPaintNode() == "char")
    {
        //Draw the text contained within each paragraph node. New lines are
        //only added after each paragraph node--not any other element.
        if (positionSet)
        {
            updateCurrentPosition();
        }

        char *character = currentPaintNode->returnCharacter();
        *currentCharacter = QString(*character);

        currentFont = qPainter->font();

        if (currentPaintNode->getWeight() == QFont::Bold)
        {
            currentFont.setBold(true);
        }
        else
        {
            currentFont.setBold(false);
        }
        QFontMetrics fm(currentFont);
        QRect box(QPoint(currentX, currentY), QSize(fm.width(*character),
                                                    fm.height()));

        qPainter->setFont(currentFont);
        qPainter->drawText(box, Qt::AlignCenter, QString(*character));

        updateCurrentPosition();
    }

    else if (currentPaintNode->getTypeOfPaintNode() == "node")
    {
        //Call the function again on each of the PaintNode's child paint nodes.
        //This ensures that all of the child nodes of the overall parent node
        //are drawn.
        std::vector<PaintNode*> *childPaintNodes = currentPaintNode->
                returnNode()->getPaintNodes();
        drawDocument(qPainter, childPaintNodes);
        if (currentPaintNode->returnNode()->getTypeOfRenderNode() == "p")
        {
            insertLineBreak();
        }
    }
}

//This adjusts the location where the next character will be drawn, including
//changing lines when the total length exceeds the width of the window.
void PaintArea::updateCurrentPosition()
{

    //positionSet is only true when the entire text has been drawn.
    //If it is false, then it is safe to set the character to the spot
    //after the current character.
    if (!positionSet)
    {
        QFont font;
        QFontMetrics fm(currentFont);

        totalWidth += fm.width(*currentCharacter);

        if (totalWidth >= this->width() - RIGHT_SIDE_X)
        {
            currentX = STARTING_X;
            currentY += (fm.height() + 2);
            totalWidth = 0;
        }
        else
        {
            currentX += fm.width(*currentCharacter);
        }
    }

    //However, if positionSet is true, then it is time to draw the entire
    //document again, so we reset the current position to the initial state.
    else
    {
        currentX = STARTING_X;
        currentY = STARTING_Y;
        totalWidth = 0;
        positionSet = false;
    }
}
