#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "htmlreader.h"
#include "elements/HTMLHeadElement.h"
#include "elements/HTMLBodyElement.h"
#include "elements/HTMLBElement.h"
#include "nodes/textnode.h"
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

//I hate myself for writing this function. I really do.
//Someday soon, when I don't have any ideas for adding
//features, I'll do some major refactoring and actually
//break it into about fifty functions, like it deserves.
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
            std::string tagNameString;
            while (currentState == tagName)
            {

                tagNameString.push_back(*i);

                i++;
                if (*i == '>')
                {
                    currentState = endTagOpen;
                }

                if (*i == ' ')
                {
                    currentState = endTagName;
                }
            }

            if (tagNameString == "p")
            {
                if (currentState == endTagName)
                {
                    while (currentState == endTagName)
                    {
                        i++;
                        if (*i == '>')
                        {
                            currentState = text;
                        }
                    }
                }
                currentState = text;
                std::string textString;
                while (currentState == text)
                {
                    i++;
                    if (*i == '<')
                    {
                        i++;
                        if (*i == '/')
                        {
                            currentState = endTagName;
                        }

                        else
                        {
                            std::string nameOfNode;
                            while (*i != '>')
                            {
                                nameOfNode.push_back(*i);
                                i++;
                            }

                            //Yes, the implementation of this sucks. For that matter,
                            //the entire implementation of TextNode sucks. This, along
                            //with rewriting the parser, is one of my top two things
                            //to do as soon as Stats is done.
                            if (nameOfNode == "b")
                            {
                                HTMLBElement bElement;
                                RenderNode *bNode = new BNode;
                                bNode = bElement.returnNode();
                                bNode->setIsOpen(true);

                                RenderNode *backupParentNode = currentParentNode;

                                currentParentNode = currentNode;
                                currentNode = bNode;

                                i++;
                                std::string textInNode;
                                while (*i != '<')
                                {
                                    textInNode.push_back(*i);
                                    i++;
                                }

                                bNode->setText(textInNode);
                                webpage->constructTree(currentNode, currentParentNode);
                                currentParentNode = backupParentNode;

                                i++;
                                currentState = endTagName;
                            }
                        }
                    }
                    else
                    {
                        textString.push_back(*i);
                    }
                }
                TextNode *textNode = new TextNode;
                textNode->setText(textString);
                currentNode = textNode;
                webpage->constructTree(currentNode, currentParentNode);
            }

            if (tagNameString == "html")
            {
                HTMLHeadElement headElement;
                RenderNode *head;
                head = headElement.returnNode();
                head->setIsOpen(true);

                currentParentNode = head;
                currentNode = head;

                webpage->constructTree(currentNode, NULL);
            }

            if (tagNameString == "body")
            {
                if (webpage->getFirstNode() == NULL)
                {
                    HTMLHeadElement headElement;
                    RenderNode *head = new RenderNode;
                    head = headElement.returnNode();
                    head->setIsOpen(true);

                    currentParentNode = head;
                    currentNode = head;

                    webpage->constructTree(currentNode, NULL);
                }

                HTMLBodyElement bodyElement;
                RenderNode *body = new RenderNode;
                body = bodyElement.returnNode();
                body->setIsOpen(true);

                currentNode = body;

                webpage->constructTree(currentNode, currentParentNode);

                currentParentNode = body;
            }
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
                documentText = documentText + "\n" + temporaryString;
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
