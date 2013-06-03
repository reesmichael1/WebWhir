#include <iostream>
#include <string>
#include <vector>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
    childNodes = new std::vector<RenderNode*>;
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

RenderNode* RenderNode::getParentNode()
{
    return parentNode;
}

void RenderNode::addChildNode(RenderNode *nodeToAdd)
{
    childNodes->push_back(nodeToAdd);
}

std::vector<RenderNode*>* RenderNode::getChildNodes()
{
    return childNodes;
}

void RenderNode::setNeedsPainting(bool valueToSet)
{
    needsPainting = valueToSet;
}

void RenderNode::paintNode()
{
    std::cout << "Node " << typeOfNode << " has " << childNodes->size() << " children." << std::endl;
}

void RenderNode::setText(std::string textToSet)
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
