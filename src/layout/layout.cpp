#include "layout.h"

Layout::Layout()
{
    size = QSize(0, 0);
    origin = QPoint(0, 0);
}

void Layout::addPaintNode(PaintNode *nodeToAdd)
{
    QSize nodeSize = nodeToAdd->getDimensions();
    nodeToAdd->setCoordinates(origin);

    origin.setY(origin.y() + nodeSize.height());
    size.setHeight(size.height() + nodeSize.height());
}

void Layout::reset()
{
    origin = QPoint(0, 0);
    size = QSize(0, 0);
}

int Layout::getHeight()
{
    return size.height();
}
