#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "htmlreader.h"
#include "elements/HTMLHeadElement.h"
#include "elements/HTMLBodyElement.h"
#include "elements/HTMLBElement.h"
#include "elements/HTMLParagraphElement.h"
#include "painter/paintnode.h"

HTMLReader::HTMLReader()
{
    currentNode = new RenderNode;
    currentParentNode = new RenderNode;
}

HTMLReader::~HTMLReader()
{
    delete webpage;
}

void HTMLReader::setPainter(Painter *painterToSet)
{
    painter = painterToSet;
}

Document *HTMLReader::parseDocumentText(std::string documentText)
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

            currentNode = createNode(tagNameString, currentState);


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
                    i++;
                }
            }

            if (tagDataString == "html")
            {
                return webpage;
            }

            while (!parentNodeClosed(currentNode, tagDataString))
            {
            }

            currentParentNode = currentNode->getParentNode();

            currentState = text;

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
        else if (currentState == bogusComment)
        {
            while (currentState == bogusComment)
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
            else
            {
                currentNode->addCharacter(i);

                std::string characterString;
                characterString.clear();
                characterString.push_back(i[0]);
                const char *characterToAdd = characterString.c_str();
                PaintNode *character = new PaintNode(*characterToAdd, painter);
                currentNode->addPaintNode(character);
            }
        }
    }

    return webpage;
}

Document* HTMLReader::prepareDocument(std::string HTMLFilepath)
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

        Document *document = parseDocumentText(documentText);

        return document;

    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
        return NULL;
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

RenderNode* HTMLReader::createNode(std::string nodeName,
                                   parseState &currentState)
{
    RenderNode *node = new RenderNode;
    if (nodeName == "html")
    {
        node = createFirstNode();
    }
    else if (nodeName == "p")
    {
        node = createParagraphNode(currentState);
    }
    else if (nodeName == "b")
    {
        node = createBNode(currentState);
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

    PaintNode *paintNode = new PaintNode(node, painter);
    currentParentNode->addPaintNode(paintNode);

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

ParagraphNode* HTMLReader::createParagraphNode(parseState &currentState)
{

    currentState = text;

    HTMLParagraphElement pElement;
    ParagraphNode *paragraphNode = new ParagraphNode;
    paragraphNode = pElement.returnNode();
    paragraphNode->setIsOpen(true);

    return paragraphNode;
}

BNode* HTMLReader::createBNode(parseState &currentState)
{
    currentState = text;

    HTMLBElement bElement;
    BNode *bNode = new BNode;
    bNode = bElement.returnNode();
    bNode->setIsOpen(true);

    return bNode;
}

HeadNode* HTMLReader::createHeadNode()
{
    HTMLHeadElement headElement;
    HeadNode *head = new HeadNode;
    head = headElement.returnNode();
    head->setIsOpen(true);

    return head;
}

BodyNode* HTMLReader::createBodyNode()
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
        currentNode = currentNode->getParentNode();

        return true;
    }
    else
    {
        currentNode = currentNode->getParentNode();
        return false;
    }
}
