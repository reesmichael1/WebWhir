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

#define TAG_START_LOCATION 1

HTMLReader::HTMLReader()
{
}

HTMLReader::~HTMLReader()
{
    delete webpage;
}

void HTMLReader::parseTagsIntoNodes()
{
    for (unsigned int i = 0; i < webpage->getVectorOfTags().size(); i++)
    {
        std::cout << webpage->getVectorOfTags().size();

        std::string tag = webpage->getVectorOfTags().at(i);
        if (tag.at(TAG_START_LOCATION) == '/')
        {
            int lengthOfTag = 0;
            int locationOfCharacterToCheckForBracket = TAG_START_LOCATION;
            int stringStartLocation = TAG_START_LOCATION + 1;

            while (webpage->getVectorOfTags().at(i).at(
                       locationOfCharacterToCheckForBracket) != '>');
            {
                std::cout << lengthOfTag;
                lengthOfTag++;
                locationOfCharacterToCheckForBracket++;
            }

            std::string parsedTag = webpage->getVectorOfTags().at(i).substr(
                        stringStartLocation, lengthOfTag);

            std::cout << parsedTag << std::endl;
        }
    }
}

void HTMLReader::parseDocumentTags(std::string textToParse)
{
    webpage = new Document;
    char characterToCheck;
    std::cout << textToParse.length();
    for (unsigned int i = 0; i < textToParse.length(); i++)
    {
        characterToCheck = textToParse.at(i);
        if (characterToCheck == '<')
        {
            int lengthOfTag = 1;
            int locationOfCharacterToCheckForBracket = i;
            int stringStartLocation = i;

            while (textToParse.at(locationOfCharacterToCheckForBracket) != '>')
            {
                lengthOfTag++;
                locationOfCharacterToCheckForBracket++;
            }

            webpage->addTagToVector(textToParse.substr(stringStartLocation, lengthOfTag));
        }
    }
    this->parseTagsIntoNodes();
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

        std::cout << documentText << std::endl;
        this->parseDocumentTags(documentText);
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }

}
