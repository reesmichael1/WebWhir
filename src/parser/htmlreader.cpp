#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "htmlreader.h"
#include "elements/HTMLHeadElement.h"
#include "elements/HTMLBodyElement.h"
#include "elements/HTMLBElement.h"
#include "nodes/paragraphnode.h"
#include "nodes/bnode.h"
#include "document.h"

HTMLReader::HTMLReader()
{
    currentNode = new RenderNode;
    currentParentNode = new RenderNode;
}

HTMLReader::~HTMLReader()
{
    delete webpage;
}

void HTMLReader::paint()
{
    webpage->paintWebpage();
}

void HTMLReader::parseDocumentText(std::string documentText)
{

    webpage = new Document;

    parseState currentState = initialMode;

    std::string::iterator i = documentText.begin();
    for (; i != documentText.end(); i++)
    {
        if (currentState == initialMode)
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
        }
        else if (currentState == tagOpen)
        {
            if (*i == '/')
            {
                currentState = endTagName;
            }
            else if (*i == '?')
            {
                currentState = bogusComment;
            }
            else if (*i == '!')
            {
                currentState = doctypeDeclaration;
            }
            else if (isalpha(*i))
            {
                i--;
                currentState = tagName;
            }
        }
        else if (currentState == tagName)
        {
            std::string tagNameString = returnTagName(i, currentState);

            if (currentState == endTagName)
            {
                while (currentState == endTagName)
                {
                    i++;
                    if (*i == '>')
                    {
                        currentState = endTagOpen;
                    }
                }
            }

            if (currentNode->getIsOpen())
            {
                currentParentNode = currentNode;
            }

            currentNode = createNode(tagNameString, i, currentState);


            webpage->constructTree(currentNode, currentParentNode);

        }
        else if (currentState == endTagName)
        {
            std::string tagDataString;

            while (currentState == endTagName)
            {
                if (*i == '>')
                {
                    currentState = endTagOpen;
                }
                else
                {
                    tagDataString.push_back(*i);
                }
                i++;
            }

            if (tagDataString == "html")
            {
                return;
            }

            while (!parentNodeClosed(currentNode, tagDataString))
            {
                currentNode = currentNode->getParentNode();
            }
            i--;

        }
        else if (currentState == endTagOpen)
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
        }
        else if (currentState == doctypeDeclaration)
        {
            while (currentState == doctypeDeclaration)
            {
                i++;
                if (*i == '>')
                {
                    currentState = endTagOpen;
                }
            }
        }
        else if (currentState == text)
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
        }
    }
}

void HTMLReader::prepareDocument(std::string HTMLFilepath)
{
    try
    {
        std::ifstream HTMLDocument(HTMLFilepath.c_str());
        if (!HTMLDocument.is_open())
        {
            throw "Error: Could not open document.";
        }

        std::string documentText;
        std::string temporaryString;

        while (!HTMLDocument.eof())
        {
            std::getline(HTMLDocument, temporaryString);
            if (!documentText.empty())
            {
                documentText = documentText + temporaryString;
            }
            else
            {
                documentText = temporaryString;
            }
        }

        HTMLDocument.close();

        parseDocumentText(documentText);

    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }

}

std::string HTMLReader::returnTagName(std::string::iterator &i,
                                      parseState &currentState)
{
    std::string tagNameString;

    while (currentState == tagName)
    {

        tagNameString.push_back(*i);

        i++;
        if (*i == '>')
        {
            currentState = endTagOpen;
        }

        else if (*i == ' ')
        {
            currentState = endTagName;
        }
    }

    return tagNameString;
}

RenderNode* HTMLReader::createNode(std::string nodeName, std::string::iterator &i,
                                   parseState &currentState)
{
    RenderNode *node = new RenderNode;
    if (nodeName == "html")
    {
        node = createFirstNode();
    }
    else if (nodeName == "p")
    {
        node = createParagraphNode(i, currentState);
    }

    else if (nodeName == "head")
    {
        node = createHeadNode();
        currentParentNode = webpage->getFirstNode();
    }

    else if (nodeName == "body")
    {
        node = createBodyNode();
        currentParentNode = webpage->getFirstNode();
    }

    return node;
}

RenderNode* HTMLReader::createFirstNode()
{
    RenderNode *firstNode = new RenderNode;
    firstNode->setParentNode(NULL);
    firstNode->setTypeOfNode("html");
    firstNode->setIsOpen(true);

    return firstNode;
}

ParagraphNode* HTMLReader::createParagraphNode(std::string::iterator &i,
                                               parseState &currentState)
{

    currentState = text;
    std::string textString;
    while (currentState == text)
    {
        i++;
        if (*i == '<')
        {
            currentState = tagOpen;
        }
        else
        {
            textString.push_back(*i);
        }
    }
    ParagraphNode *paragraphNode = new ParagraphNode;
    paragraphNode->setText(textString);

    return paragraphNode;
}

HeadNode* HTMLReader::createHeadNode()
{
    HTMLHeadElement headElement;
    HeadNode *head = new HeadNode;
    head = headElement.returnNode();
    head->setIsOpen(true);

    return head;
}

BodyNode *HTMLReader::createBodyNode()
{
    HTMLBodyElement bodyElement;
    BodyNode *body = new BodyNode;

    body = bodyElement.returnNode();
    body->setIsOpen(true);

    return body;

}

bool HTMLReader::parentNodeClosed(RenderNode *node, std::string typeOfNode)
{
    if (node->getTypeOfNode() == typeOfNode)
    {
        node->setIsOpen(false);
        return true;
    }
    else
    {
        return false;
    }
}
