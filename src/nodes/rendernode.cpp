#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
    childNodes = new std::vector<RenderNode*>;
}

RenderNode::~RenderNode()
{
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

void RenderNode::paintNode(std::string *webpageString)
{

    std::string childVectorSize;
    std::stringstream out;
    out << childNodes->size();
    childVectorSize = out.str();

    std::string temporaryString = "Node " + typeOfNode + " has "
            + childVectorSize + " children.\n";

    *webpageString += temporaryString;

}

void RenderNode::setText()
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
