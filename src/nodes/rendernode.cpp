#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
    childNodes = new std::vector<RenderNode*>;
    paintNodes = new std::vector<PaintNode*>;
}

RenderNode::~RenderNode()
{
    deleteChildNodes();
    deletePaintNodes();
}

void RenderNode::setTypeOfRenderNode(std::string typeToSet)
{
    typeOfNode = typeToSet;
}

std::string RenderNode::getTypeOfRenderNode()
{
    return typeOfNode;
}

void RenderNode::setParentNode(RenderNode *nodeToSet)
{
    parentNode = nodeToSet;
}


std::string RenderNode::getSourcePath()
{
    return NULL;
}

std::string RenderNode::getAltText()
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

void RenderNode::addPaintNode(PaintNode *nodeToAdd)
{
    paintNodes->push_back(nodeToAdd);
}

void RenderNode::deleteChildNodes()
{
    while (!childNodes->empty())
    {
        delete childNodes->back();
        childNodes->pop_back();
    }
}

void RenderNode::deletePaintNodes()
{
    while (!paintNodes->empty())
    {
        delete paintNodes->back();
        paintNodes->pop_back();
    }
}

std::vector<RenderNode*>* RenderNode::getChildNodes()
{
    return childNodes;
}

std::vector<PaintNode*>* RenderNode::getPaintNodes()
{
    return paintNodes;
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
