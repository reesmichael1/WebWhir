#include "paintnode.h"

PaintNode::PaintNode(RenderNode *node)
{
    bold = false;
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
