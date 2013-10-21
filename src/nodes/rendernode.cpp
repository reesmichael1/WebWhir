#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
    childNodes = new std::vector<RenderNode*>;

    typeOfNode = new std::string;
}

RenderNode::RenderNode(std::string nodeText)
{
    needsPainting = true;
    childNodes = new std::vector<RenderNode*>;

    typeOfNode = new std::string;
    text = new std::string;
    setIsOpen(false);
    *text = nodeText;
}

RenderNode::~RenderNode()
{
    deleteChildNodes();
}

void RenderNode::setTypeOfRenderNode(std::string typeToSet)
{
    *typeOfNode = typeToSet;
}

std::string RenderNode::getTypeOfRenderNode()
{
    return *typeOfNode;
}

void RenderNode::setParentNode(RenderNode *nodeToSet)
{
    parentNode = nodeToSet;
}


std::string* RenderNode::getSourcePath()
{
    std::string *hello = new std::string;
    *hello = "Hello world.";
    return hello;
}

std::string* RenderNode::getAltText()
{
    return NULL;
}

RenderNode* RenderNode::getParentNode()
{
    return parentNode;
}

void RenderNode::addChildNode(RenderNode *nodeToAdd)
{
    childNodes->push_back(nodeToAdd);
}

void RenderNode::deleteChildNodes()
{
    while (!childNodes->empty())
    {
        delete childNodes->back();
        childNodes->pop_back();
    }
}

std::vector<RenderNode*>* RenderNode::getChildNodes()
{
    return childNodes;
}

void RenderNode::setNeedsPainting(bool valueToSet)
{
    needsPainting = valueToSet;
}

void RenderNode::setIsOpen(bool valueToSet)
{
    isOpen = valueToSet;
}

bool RenderNode::getIsOpen()
{
    return isOpen;
}
