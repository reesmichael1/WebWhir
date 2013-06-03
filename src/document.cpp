#include <iostream>
#include <string>
#include "nodes/rendernode.h"
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
    //This has the potential to crash if parentNode is somehow passed as NULL.
    //I will work on this.
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

void Document::paintChildren(RenderNode *parentNode)
{
    std::vector<RenderNode*> *childNodesVector = parentNode->getChildNodes();
    if (!childNodesVector->empty())
    {
        for (std::vector<RenderNode*>::iterator i = childNodesVector->begin(); i != childNodesVector->end(); i++)
        {
            (*i)->paintNode();
            paintChildren(*i);
        }
    }
}

void Document::paintWebpage()
{
    try
    {
        if (firstNode == NULL)
        {
            throw "Error: Webpage is empty.";
        }

        firstNode->paintNode();

        paintChildren(firstNode);
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}
