#include "paintnode.h"
#include "ParagraphPaintNode.h"

PaintNode::PaintNode()
{
    needsPainting = true;
}

void PaintNode::paint(QPainter *qPainter, PaintArea *display)
{
    paintChildNodes(qPainter, display);
    return;
}

void PaintNode::paintChildNodes(QPainter *qPainter, PaintArea *display)
{
    for (std::vector<PaintNode*>::iterator i = childPaintNodes.begin();
         i != childPaintNodes.end(); i++)
    {
        (*i)->paint(qPainter, display);
    }
}

void PaintNode::addChildPaintNodes(std::vector<PaintNode*> childNodes)
{
    childPaintNodes = childNodes;
}

QSize PaintNode::getDimensions()
{
    return QSize(0, 0);
}
