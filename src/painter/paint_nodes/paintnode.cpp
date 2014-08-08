#include "paintnode.h"

PaintNode::PaintNode()
{
    needsPainting = true;
    dimensions = QSize(0, 0);
    coordinates = QPoint(0, 0);
    inlineNode = false;
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

void PaintNode::paint(WWPainter *wwPainter, PaintArea *display, Layout *layout)
{
    paintChildNodes(wwPainter, display, layout);
    return;
}

void PaintNode::paintChildNodes(WWPainter *wwPainter, PaintArea *display,
                                Layout *layout)
{
    for (std::vector<PaintNode*>::iterator i = childPaintNodes.begin();
         i != childPaintNodes.end(); i++)
    {
        (*i)->calculateDimensions(display);
        (*i)->paint(wwPainter, display, layout);
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
}

QSize PaintNode::getDimensions()
{
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

void PaintNode::setIsInline(bool inlineOrNot)
{
    inlineNode = inlineOrNot;
}

bool PaintNode::isInlineNode()
{
    return inlineNode;
}
