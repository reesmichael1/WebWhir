#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "coloroperations.h"
#include "htmlreader.h"
#include "textnode.h"
#include "painter.h"

HTMLReader::HTMLReader()
{
}

void HTMLReader::parseDocument(char HTMLFilepath[])
{

    try
    {
        std::ifstream HTMLDocument(HTMLFilepath);
        if (!HTMLDocument.is_open())
        {
            throw "Error: Could not open document.";
        }

        std::string line;
        TextNode node;

        std::getline(HTMLDocument, line);

        if (line.empty())
        {
            throw "Error: Document is empty.";
        }

        while (!HTMLDocument.eof())
        {
            if (line.find("TextBackgroundColor:") != std::string::npos)
            {
                line.erase(line.begin(), line.begin()+20);
                node.setTextBackgroundColor(sf::Color::White);
                node.setTextBackgroundColor(ColorOperations::convertStringToColor(line));
                std::getline(HTMLDocument, line);
            }
            if (line.find("BackgroundColor:") != std::string::npos)
            {
                line.erase(line.begin(), line.begin()+16);
                node.setBackgroundColorOfNode(ColorOperations::convertStringToColor(line));
                std::getline(HTMLDocument, line);
            }
            if (line.find("TextColor:") != std::string::npos)
            {
                line.erase(line.begin(), line.begin()+10);
                node.setCharacterColor(sf::Color::White);
                node.setCharacterColor(ColorOperations::convertStringToColor(line));
                std::getline(HTMLDocument, line);
            }
            if (line.find("TextSize") != std::string::npos)
            {
                line.erase(line.begin(), line.begin()+9);
                int characterSize;
                std::istringstream(line) >> characterSize;
                node.setTextCharacterSize(characterSize);
                std::getline(HTMLDocument, line);
            }
            else
            {
                node.appendText(&line);
                std::getline(HTMLDocument, line);
            }
        }

        Painter display(&node);
        HTMLDocument.close();
    }

    catch (char error[])
    {
        std::cerr << error << std::endl;
    }

}
