#include "parser/htmlreader.h"

void HTMLReader::initialModeCase(parseState& currentState, std::string::iterator &i)
{
    if (*i == '<')
    {
        currentState = tagOpen;
    }
}

void HTMLReader::tagOpenCase(parseState &currentState, std::string::iterator &i)
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

}

void HTMLReader::tagNameCase(parseState &currentState, std::string::iterator &i,
                             std::string HTMLFilepath)
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
}

Document* HTMLReader::endTagNameCase(parseState &currentState, std::string::iterator &i)
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
    return NULL;
}

void HTMLReader::endTagOpenCase(parseState &currentState, std::string::iterator &i)
{
    if (*i == '<')
    {
        currentState = tagOpen;
    }
}

void HTMLReader::bogusCommentCase(parseState &currentState, std::string::iterator &i)
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
}

void HTMLReader::doctypeDeclarationCase(parseState &currentState, std::string::iterator &i)
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

void HTMLReader::textCase(parseState &currentState, std::string::iterator &i)
{
    if (*i == '<')
    {
        currentState = tagOpen;
    }
    else
    {
        std::string nodeText;

        while (*i != '<')
        {
            nodeText.push_back(*i);
            i++;
        }

        i--;

        currentNode->addText(nodeText);
    }
}
