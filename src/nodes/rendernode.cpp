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

void RenderNode::addPaintNode(PaintNode *nodeToAdd)
{
    paintNodes->push_back(nodeToAdd);
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

/*
void RenderNode::paintNode()
{

    std::vector<PaintNode*>::iterator iterator;
    for (iterator = paintNodes->begin(); iterator != paintNodes->end();
         iterator++)
    {
        (*iterator)->paint();
    }
}
*/

void RenderNode::addCharacter(std::string::iterator i)
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
