#include <iostream>
#include <vector>
#include <memory>
//#include <sstream>
#include <fstream>
#include <string>
#include "coloroperations.h"
#include "htmlreader.h"
#include "textnode.h"
#include "painter.h"

HTMLReader::HTMLReader()
{
}

/*
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
*/

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

        std::getline(HTMLDocument, line);

        if (line.empty())
        {
            throw "Error: Document is empty.";
        }

        std::vector<std::unique_ptr<RenderNode>> vectorOfNodes;

        while (!HTMLDocument.eof())
        {

            if (line.find("<") != std::string::npos)
            {
                line.erase(line.begin(), line.begin()+1);
                if (line.at(0) == 'p')
                {
                    line.erase(line.begin(), line.begin()+2);
                    TextNode *textNode = new TextNode;
                    line.erase(line.end() - 4, line.end());
                    textNode->setText(line);
                    vectorOfNodes.emplace_back(textNode);
                }
                else
                {
                    std::cout << "\n\nUnknown tag in line: <" << line << std::endl;
                }
            }

            std::getline(HTMLDocument, line);
        }

        Painter painterOfNodes;
        painterOfNodes.paintNodes(&vectorOfNodes);

    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }

}
