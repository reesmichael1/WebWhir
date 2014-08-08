#include "layout.h"

Layout::Layout()
{
    reset();
}

void Layout::reset()
{
    origin = QPoint(0, 0);
    size = QSize(0, 0);
    lastX = 0;
}

void Layout::addPaintNode(PaintNode *nodeToAdd)
{
    QSize nodeSize = nodeToAdd->getDimensions();
    if (nodeToAdd->isInlineNode())
    {
        lastX = calculateNewXAfterAddingNode(nodeToAdd);
        origin.setX(origin.x() + lastX);
    }
    else
    {
        lastX = nodeToAdd->getWidth();
        origin.setX(0);
        origin.setY(origin.y() + nodeSize.height());
    }
    nodeToAdd->setCoordinates(origin);

    size.setHeight(size.height() + nodeSize.height());
}

int Layout::calculateNewXAfterAddingNode(PaintNode *newNode)
{
    int newX = lastX;
    newX += newNode->getWidth();
    return newX;
}

int Layout::getHeight()
{
    return size.height();
}

QPoint Layout::getOrigin()
{
    return origin;
}

QSize Layout::getSize()
{
    return size;
}
