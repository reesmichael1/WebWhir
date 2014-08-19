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
    nodeToAdd->setCoordinates(origin);
    origin.setY(origin.y() + nodeSize.height());
    nodeToAdd->setXCoordinateOfEdgeOfFirstLine(lastX);
    lastX = nodeToAdd->getXCoordinateOfEdgeOfLastLine();

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
