#include <iostream>
#include <string>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
}

void RenderNode::setTypeOfNode(std::string typeToSet)
{
    typeOfNode = typeToSet;
}

std::string RenderNode::getTypeOfNode()
{
    return typeOfNode;
}

void RenderNode::setParentNode(RenderNode *nodeToSet)
{
    parentNode = nodeToSet;
}

void RenderNode::addChildNode(RenderNode *nodeToAdd)
{
    childNodes.push_back(nodeToAdd);
}

void RenderNode::setNeedsPainting(bool valueToSet)
{
    needsPainting = valueToSet;
}

void RenderNode::paintNode()
{
}

void RenderNode::setIsOpen(bool valueToSet)
{
    isOpen = valueToSet;
}

bool RenderNode::getIsOpen()
{
    return isOpen;
}
