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

void Document::constructTree(RenderNode *nodeToAdd)
{

    if (firstNode == NULL)
    {
        firstNode = nodeToAdd;
        firstNode->setChildNode(NULL);
    }
    else
    {
        RenderNode *iterator;
        iterator = firstNode;
         while (iterator->getChildNode() != NULL)
        {
            iterator = iterator->getChildNode();
        }

        iterator->setChildNode(nodeToAdd);

        iterator = iterator->getChildNode();
        iterator->setChildNode(NULL);

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

        RenderNode *iterator;
        iterator = firstNode;
        while (iterator->getChildNode() != NULL)
        {
            iterator->paintNode();
            iterator = iterator->getChildNode();
        }

        iterator->paintNode();
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}
