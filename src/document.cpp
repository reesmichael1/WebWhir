#include <iostream>
#include <string>
#include "document.h"

//The document class is the representation of the webpage in nodes. When the
//parser creates render nodes, they are strung together in a kind-of-linked
//list, and paint nodes are added to the render nodes as children. This
//list is stored within the document, and is how the webpage is painted.

Document::Document()
{
    firstNode = new RenderNode;
    firstNode = NULL;
}

Document::~Document()
{
    clearTree();
}

RenderNode* Document::getFirstNode()
{
    return firstNode;
}

std::string Document::getDocumentTitle()
{
    return documentTitle;
}

void Document::setDocumentTitle(std::string titleToSet)
{
    documentTitle = titleToSet;
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

void Document::clearTree()
{
    delete firstNode;
    firstNode = new RenderNode;
    firstNode = NULL;
}
