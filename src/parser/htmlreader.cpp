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

Document *HTMLReader::parseDocumentText(std::string documentText)
{

    webpage = new Document;

    parseState currentState = initialMode;

    //The parser works by moving through the document text one character
    //at a time. Various states are defined, and, depending on what the
    //current state is when a certain character is reached, a different
    //action is taken for each state/character combination.
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
            //Create a new node.
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

            //Define newly created node as child of current node
            //if the current node hasn't been closed.
            if (currentNode->getIsOpen())
            {
                currentParentNode = currentNode;
            }

            currentNode = createNode(tagNameString, currentState);

            //Add newly created node to tree of nodes.
            webpage->constructTree(currentNode, currentParentNode);

        }
        else if (currentState == endTagName)
        {
            //Close the current node.
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
                //We've reached the end of the document (assuming the author
                //actually followed web standards!).
                return webpage;
            }

            //Move up through the tree a node at a time
            //until we find the node being closed.
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
            //Unfortunately, I have to ignore doctypes for now...I simply don't
            //have the resources to create multiple engines for each doctype.
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
            //This assumes comments are properly written
            //(it does not check to confirm it is not "bogus").
            //It just glazes over any comments it hits.
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
                //Add text to the current node.
                //currentNode->addCharacter(i);

                //Create a paint node that is
                //a child of the current Render Node.
                std::string characterString;
                characterString.clear();
                characterString.push_back(i[0]);
                const char *characterToAdd = characterString.c_str();
                PaintNode *character = new PaintNode(*characterToAdd);

                if (currentNode->getTypeOfRenderNode() == "b")
                {
                    character->setWeight(QFont::Bold);
                }

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

        //Parse entire document into one string.
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

        //Create a Document by parsing through
        //the string created from the HTML file.
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

    PaintNode *paintNode = new PaintNode(node);
    currentParentNode->addPaintNode(paintNode);

    return node;
}

RenderNode* HTMLReader::createFirstNode()
{
    //This node is necessary because it acts as the parent node
    //for both the head and body nodes.
    RenderNode *firstNode = new RenderNode;
    firstNode->setParentNode(NULL);
    firstNode->setTypeOfRenderNode("html");
    firstNode->setIsOpen(true);

    return firstNode;
}

//Each of the create*node() functions use elements to do so. This doesn't mean
//anything yet, but will be used once inline attributes are supported.

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
    if (node->getTypeOfRenderNode() == typeOfNode)
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
