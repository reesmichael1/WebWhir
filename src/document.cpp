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

void Document::paintChildren(RenderNode *parentNode, std::string *webpageString)
{
    std::vector<RenderNode*> *childNodesVector = parentNode->getChildNodes();
    if (!childNodesVector->empty())
    {
        for (std::vector<RenderNode*>::iterator i = childNodesVector->begin(); i != childNodesVector->end(); i++)
        {
            (*i)->paintNode(webpageString);
            paintChildren(*i, webpageString);
        }
    }
}

void Document::paintWebpage(std::string *webpageString)
{
    try
    {
        if (firstNode == NULL)
        {
            throw "Error: Webpage is empty.";
        }

        firstNode->paintNode(webpageString);

        paintChildren(firstNode, webpageString);
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}
