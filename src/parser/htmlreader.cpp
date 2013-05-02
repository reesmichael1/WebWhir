#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include "coloroperations.h"
#include "htmlreader.h"
#include "textnode.h"
#include "document.h"

HTMLReader::HTMLReader()
{
}

HTMLReader::~HTMLReader()
{
    delete webpage;
}

void HTMLReader::parseDocumentText(std::string documentText)
{
    parseState currentState = initialMode;

    webpage = new Document;

    std::string::iterator i = documentText.begin();
    for (; i != documentText.end(); i++)
    {
        //std::cout << *i;
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
                currentState == endTagOpen;
            }
            else if (*i == '?')
            {
                currentState == bogusComment;
            }
            else if (isalpha(*i))
            {
                std::cout << "Entered tag." << std::endl;
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
