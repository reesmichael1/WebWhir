#include "paintarea.h"

#include <QMessageBox>

#define STARTING_X 10

//Padding from the right side of the window
#define RIGHT_SIDE_PADDING 10
#define LIST_PADDING 50
#define STARTING_Y 10

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    currentX = STARTING_X;
    currentY = STARTING_Y;
    totalWidth = 0;

    webpage = new Document;
    positionSet = false;

    currentCharacter = new QString;

    indentOn = false;
    nextWordChecked = false;
}

PaintArea::~PaintArea()
{
    delete webpage;
    delete currentCharacter;
}

void PaintArea::setDocument(Document *documentToSet)
{
    webpage = documentToSet;
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (webpage->getFirstNode() != NULL)
    {

        QPainter qPainter(this);

        //Prevents document from moving around while being redrawn.
        positionSet = true;

        //This is necessary to show the entire paint area in the scroll area.
        setMinimumHeight(currentY);
        setMaximumHeight(currentY);
    }
}

void PaintArea::insertLineBreak()
{
    QFont font = currentFont;
    QFontMetrics fm(font);

    if (!indentOn)
    {
        currentX = STARTING_X;
        currentY += 2 * fm.height();
        totalWidth = 0;
    }

    else
    {
        currentX = STARTING_X + LIST_PADDING;
        currentY -= fm.height();
        totalWidth = 0;
    }
}


//This adjusts the location where the next character will be drawn, including
//changing lines when the total length exceeds the width of the window.
void PaintArea::updateCurrentPosition()
{

    //positionSet is only true when the entire document has been drawn.
    //If it is false, then it is safe to set the character to the spot
    //after the current character.
    if (!positionSet)
    {
        QFontMetrics fm(currentFont);

        totalWidth += fm.width(*currentCharacter);
        currentX += fm.width(*currentCharacter);
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
