#include <iostream>
#include <vector>
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
    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }

}
