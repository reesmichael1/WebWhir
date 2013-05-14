#include <iostream>
#include "rendernode.h"
#include "document.h"

Document::Document()
{
    firstNode = NULL;
}

void Document::constructTree(RenderNode *nodeToAdd)
{

    if (firstNode == NULL)
    {
        firstNode = nodeToAdd;
        firstNode->childNode = NULL;
    }
    else
    {
        RenderNode *iterator;
        iterator = firstNode;
        while (iterator->childNode != NULL)
        {
            iterator = iterator->childNode;
        }

        iterator->childNode = nodeToAdd;

        iterator = iterator->childNode;
        iterator->childNode = NULL;
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
        while (iterator->childNode != NULL)
        {
            std::cout << iterator->getText() << std::endl;
            iterator = iterator->childNode;
        }

        std::cout << iterator->getText() << std::endl;
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}


