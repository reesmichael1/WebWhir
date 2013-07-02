#include <iostream>
#include <string>
#include "document.h"

Document::Document()
{
    firstNode = new RenderNode;
    firstNode = NULL;
}

Document::~Document()
{
    delete firstNode;
}

RenderNode* Document::getFirstNode()
{
    return firstNode;
}

void Document::constructTree(RenderNode *childNode, RenderNode *parentNode)
{   
    //This is here to prevent a crash if parentNode is passed as null.
    //It has not been tested, and the ramifications are unexplored.
    if (parentNode == NULL)
    {
        parentNode = firstNode;
    }
    if (firstNode == NULL)
    {
        firstNode = childNode;
    }
    else
    {
        childNode->setParentNode(parentNode);
        parentNode->addChildNode(childNode);
    }
}
