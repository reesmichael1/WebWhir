#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
    childNodes = new std::vector<RenderNode*>;
    text = "";

    typeOfNode = new std::string;
}

RenderNode::RenderNode(std::string nodeText)
{
    needsPainting = true;
    childNodes = new std::vector<RenderNode*>;

    typeOfNode = new std::string;
    setIsOpen(false);
    text = nodeText;
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

PaintNode* RenderNode::convertToPaintNode()
{
    PaintNode *paintNode = new PaintNode;
    paintNode->addChildPaintNodes(convertChildNodesToPaintNodes());

    return paintNode;
}

std::vector<PaintNode*> RenderNode::convertChildNodesToPaintNodes()
{
    std::vector<PaintNode*> childPaintNodes;
    for (std::vector<RenderNode*>::iterator i = childNodes->begin();
         i != childNodes->end(); i++)
    {
        childPaintNodes.push_back((*i)->convertToPaintNode());
    }

    return childPaintNodes;
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

void RenderNode::setText(std::string textToSet)
{
    text = textToSet;
}

std::string RenderNode::getText()
{
    return text;
}

bool RenderNode::getIsOpen()
{
    return isOpen;
}
