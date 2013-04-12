#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include "coloroperations.h"
#include "htmlreader.h"
#include "textnode.h"
#include "painter.h"
#include "document.h"

HTMLReader::HTMLReader()
{
}

HTMLReader::~HTMLReader()
{
    delete webpage;
}


void HTMLReader::parseDocument(std::string textToParse)
{
    webpage = new Document;
    char characterToCheck;
    for (unsigned int i = 0; i < textToParse.length(); i++)
    {
        characterToCheck = textToParse.at(i);
        if (characterToCheck == '<')
        {
            int checkForBracket = i;
            do
            {
                checkForBracket++;
            } while (textToParse.at(checkForBracket != '>'));
            webpage->addTagToVector(textToParse.substr(i++, checkForBracket));
            i--;
        }
    }
}

void HTMLReader::prepareDocument(char HTMLFilepath[])
{
    try
    {
        std::ifstream HTMLDocument(HTMLFilepath);
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

         this->parseDocument(documentText);
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }

}
