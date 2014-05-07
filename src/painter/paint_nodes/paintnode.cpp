#include "paintnode.h"

PaintNode::PaintNode()
{
    bold = false;
    dirty = true;
    text = "";
}

PaintNode::PaintNode(RenderNode *node)
{
    bold = false;
    dirty = true;
    text = "";

    if (node->getTypeOfRenderNode() == "b")
    {
        bold = true;
    }

    if (node->getText() != "")
    {
        text = node->getText();
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
