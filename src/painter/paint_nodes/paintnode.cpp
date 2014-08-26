#include "paintnode.h"

PaintNode::PaintNode()
{
    needsPainting = true;
    dimensions = QSize(0, 0);
    coordinates = QPoint(0, 0);
    xCoordinateOfEdgeOfLastLine = 0;
    xCoordinateOfStartOfFirstLine = 0;
}

PaintNode::~PaintNode()
{
    emptyChildPaintNodes();
}

void PaintNode::emptyChildPaintNodes()
{
    while (!childPaintNodes.empty())
    {
        delete childPaintNodes.back();
        childPaintNodes.pop_back();
    }
}

void PaintNode::paint(WWPainter &wwPainter, PaintArea *display, Layout *layout)
{
    paintChildNodes(wwPainter, display, layout);
    return;
}

void PaintNode::paintChildNodes(WWPainter &wwPainter, PaintArea *display,
                                Layout *layout)
{
    for (PaintNode* childPaintNode : childPaintNodes)
    {
        childPaintNode->paint(wwPainter, display, layout);
    }
}

void PaintNode::addChildPaintNodes(std::vector<PaintNode*> childNodes)
{
    childPaintNodes = childNodes;
}

std::vector<PaintNode*> PaintNode::getChildPaintNodes()
{
    return childPaintNodes;
}

void PaintNode::setCoordinates(QPoint coordinatesToSet)
{
    if (!(coordinates == coordinatesToSet))
    {
        coordinates = coordinatesToSet;
        needsPainting = true;
    }
}

QPoint PaintNode::getCoordinates()
{
    return coordinates;
}

void PaintNode::calculateDimensions(PaintArea *display)
{
    for (PaintNode* childNode : childPaintNodes)
    {
        childNode->calculateDimensions(display);
    }
}

QSize PaintNode::getDimensions(PaintArea *display)
{
    calculateDimensions(display);
    return dimensions;
}

int PaintNode::getWidth()
{
    return dimensions.width();
}

int PaintNode::getHeight()
{
    return dimensions.height();
}

std::vector<int> PaintNode::getPaintOptions()
{
    return paintOptions;
}

void PaintNode::addPaintOption(paintOption optionToAdd)
{
    paintOptions.push_back(optionToAdd);
}

void PaintNode::setXCoordinateOfStartOfFirstLine(int xToSet)
{
    xCoordinateOfStartOfFirstLine = xToSet;
}

int PaintNode::getXCoordinateOfEdgeOfLastLine()
{
    return xCoordinateOfEdgeOfLastLine;
}

void PaintNode::setNeedsPainting(bool valueToSet)
{
    needsPainting = valueToSet;
    for (PaintNode* childPaintNode : childPaintNodes)
    {
        childPaintNode->setNeedsPainting(valueToSet);
    }
}

bool PaintNode::getNeedsPainting()
{
    return needsPainting;
}

bool PaintNode::getIsInline()
{
    return isInline;
}

void PaintNode::setIsInline(bool inlineOrNot)
{
    isInline = inlineOrNot;
}

void PaintNode::resetPaintNode()
{
    xCoordinateOfEdgeOfLastLine = 0;
    xCoordinateOfStartOfFirstLine = 0;
    dimensions = QSize(0, 0);
    coordinates = QPoint(0, 0);

    for (PaintNode *childPaintNode : childPaintNodes)
    {
        childPaintNode->resetPaintNode();
    }
}
