#include <iostream>
#include "bnode.h"
#include "painter/paint_nodes/BPaintNode.h"

BNode::BNode()
{
    setNeedsPainting(true);
    setTypeOfRenderNode("b");
}

PaintNode* BNode::convertToPaintNode()
{
    BPaintNode *paintNode = new BPaintNode;
    paintNode->addChildPaintNodes(convertChildNodesToPaintNodes());

    return paintNode;
}
