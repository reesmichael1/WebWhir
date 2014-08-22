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

void Layout::addPaintNode(PaintNode *nodeToAdd, PaintArea *display)
{
    QSize nodeSize = nodeToAdd->getDimensions(display);
    nodeToAdd->setCoordinates(origin);
    if (nodeToAdd->getIsInline())
    {
        nodeToAdd->setXCoordinateOfStartOfFirstLine(lastX);
        lastX += nodeToAdd->getXCoordinateOfEdgeOfLastLine();
        if (nodeToAdd->getDimensions(display).height() != 15)
        {
            origin.setY(origin.y() + nodeSize.height());
        }
    }
    else
    {
        origin.setY(origin.y() + nodeSize.height());
        size.setHeight(size.height() + nodeSize.height());
        lastX = 0;
    }

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
