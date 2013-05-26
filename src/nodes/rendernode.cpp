#include <iostream>
#include <string>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
    childNodePointer = NULL;
}

RenderNode* RenderNode::getChildNode()
{
    return childNodePointer;
}

void RenderNode::setChildNode(RenderNode *nodeToAdd)
{
     childNodePointer = nodeToAdd;
}

void RenderNode::setNeedsPainting(bool valueToSet)
{
    needsPainting = valueToSet;
}

void RenderNode::paintNode()
{
}
