#include <iostream>
#include <fstream>
#include "htmlreader.h"

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
            throw 0;
        }
        else
        {
            std::cout << "Now entering the parser." << std::endl;
        }

        std::string line;

        while (HTMLDocument.good())
        {
            std::getline(HTMLDocument, line);
            RenderObject renderNode;
            renderNode.setText(line);
        }

        HTMLDocument.close();

        Painter::drawNode(&renderNode);

    }

    catch (int i)
    {
        if (i == 0)
        {
            std::cerr << "Error: Could not open the document." << std::endl;
        }
    }

}
