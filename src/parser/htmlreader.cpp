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
            initialModeCase(currentState, i);
            break;
        }
        case tagOpen:
        {
            tagOpenCase(currentState, i);
            break;
        }
        case tagName:
        {
            tagNameCase(currentState, i, HTMLFilepath);
            break;
        }
        case endTagName:
        {
            // Check if we've hit the </html> tag
            // If so, return the document to finish parsing
            Document *potentialNodeTree = endTagNameCase(currentState, i);
            if (potentialNodeTree)
            {
                return potentialNodeTree;
            }
            break;
        }
        case endTagOpen:
        {
            endTagOpenCase(currentState, i);
            break;
        }
        case doctypeDeclaration:
        {
            doctypeDeclarationCase(currentState, i);
            break;
        }
        case bogusComment:
        {
            bogusCommentCase(currentState, i);
            break;
        }
        case text:
        {
            textCase(currentState, i);
            break;
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

std::string HTMLReader::getTagString(std::string::iterator &i,
                       parseState &currentState)
{
    std::string tagString;
    parseState oldState = currentState;
    while (currentState == oldState)
    {
        tagString.push_back(*i);

        i++;
        if (*i == '>')
        {
            currentState = endTagOpen;
        }

        else if (*i == ' ' && oldState != text)
        {
            currentState = endTagName;
        }

        else if (*i == '<')
        {
            currentState = tagOpen;
        }
    }

    return tagString;
}

std::string HTMLReader::returnTagName(std::string::iterator &i,
                                      parseState &currentState)
{

    std::string tagNameString = getTagString(i, currentState);

    if (tagNameString == "title")
    {
        currentState = text;
        i++;
        std::string titleString = getTagString(i, currentState);
        std::string closeTitleTag = getTagString(i, currentState);

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
