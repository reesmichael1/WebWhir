#include "layout.h"

/*!
\fn void Layout::Layout()
The constructor for the Layout class.
Initialize the variable size to an empty QSize (width and height of 0) 
and the origin to the QPoint (0, 0).
Input: None
Output: None
*/
Layout::Layout()
{
    size = QSize(0, 0);
    origin = QPoint(0, 0);
}

/*!
\fn void Layout::addPaintNode(PaintNode *nodeToAdd)
Add a new \l{PaintNode} to the Layout.
This changes the size of the Layout to reflect the new node that
is contained within the Layout and changes the origin to denote where
the next \l{PaintNode} should begin.
Input: The \l{PaintNode} that will be added to the layout.
Outpu: None
*/
void Layout::addPaintNode(PaintNode *nodeToAdd)
{
    QSize nodeSize = nodeToAdd->getDimensions();
    nodeToAdd->setCoordinates(origin);

    origin.setY(origin.y() + nodeSize.height());
    size.setHeight(size.height() + nodeSize.height());
}

/*!
\fn void Layout::reset()
Reset the origin and size to (0, 0).
Input: None
Output: None
*/
void Layout::reset()
{
    origin = QPoint(0, 0);
    size = QSize(0, 0);
}

/*!
\fn int Layout::getHeight()
Get the height of the Layout.
Input: None
Output: An integer that represents the height of the bounding rectangle
around the Layout.
*/
int Layout::getHeight()
{
    return size.height();
}
