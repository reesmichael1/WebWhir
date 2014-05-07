#include "paintnode.h"
#include "ParagraphPaintNode.h"

PaintNode::PaintNode()
{
    needsPainting = true;
}

void PaintNode::addChildPaintNodes(std::vector<PaintNode*> childNodes)
{
    childPaintNodes = childNodes;
}

QSize PaintNode::getDimensions()
{
    return QSize(0, 0);
}
