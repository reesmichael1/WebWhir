#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "htmlreader.h"

HTMLReader::HTMLReader()
{
    currentNode = new RenderNode;
    currentNode = NULL;
    currentParentNode = new RenderNode;
}

HTMLReader::~HTMLReader()
{
    delete webpage;
}

Document *HTMLReader::parseDocumentText(std::string documentText,
                                        std::string HTMLFilepath)
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
        switch (currentState)
        {
        case initialMode:
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
            break;
        }
        case tagOpen:
        {
            if (*i == '/')
            {
                currentState = endTagName;
            }
            else if (*i == '!')
            {
                currentState = bogusComment;
            }
            else if (isalpha(*i))
            {
                i--;
                currentState = tagName;
            }

            break;
        }
        case tagName:
        {
            //Create a new node.
            std::string tagNameString = returnTagName(i, currentState);

            if (tagNameString != "title")
            {

                //Define newly created node as child of current node
                //if the current node hasn't been closed.
                if (currentNode != NULL)
                {
                    if (currentNode->getIsOpen())
                    {
                        currentParentNode = currentNode;
                    }
                }

                currentNode = createNode(tagNameString, currentState, i,
                                         HTMLFilepath);

                //Add newly created node to tree of nodes.
                webpage->constructTree(currentNode, currentParentNode);

                if (!currentNode->getIsOpen())
                {
                    currentNode = currentParentNode;
                }
            }

            break;
        }
        case endTagName:
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

            break;

        }
        case endTagOpen:
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }

            break;
        }
        case doctypeDeclaration:
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

            break;
        }
        case bogusComment:
        {
            //This assumes comments are properly written
            //(it does not check to confirm it is not "bogus").
            //It just glazes over any comments it hits.
            if (*i != '-')
            {
                currentState = doctypeDeclaration;
            }

            while (currentState == bogusComment)
            {
                i++;
                if (*i == '>')
                {
                    currentState = endTagOpen;
                }
            }

            break;
        }
        case text:
        {
            if (*i == '<')
            {
                currentState = tagOpen;
            }
            else
            {
                //Create a RenderNode composed of the text until the state
                //changes, and add it as a child node of the current node.
                std::string nodeText;

                while (*i != '<')
                {
                    nodeText.push_back(*i);
                    i++;
                }

                i--;

                RenderNode *textNode = new RenderNode(nodeText);
                currentNode->addChildNode(textNode);
            }
        }
            break;
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
        Document *document = parseDocumentText(documentText, HTMLFilepath);

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

    if (tagNameString == "title")
    {
        std::string titleString;

        while (currentState != tagOpen)
        {
            i++;
            if (*i == '<')
            {
                currentState = tagOpen;
            }

            else
            {
                titleString.push_back(*i);
            }
        }

        while (currentState == tagOpen)
        {
            i++;
            if (*i == '>')
            {
                currentState = endTagOpen;
            }
        }

        webpage->setDocumentTitle(titleString);
    }

    return tagNameString;
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
