#include <iostream>
#include <fstream>
#include <string>
#include "htmlreader.h"
#include "rendernode.h"
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
            throw 0;
        }

        std::string line;
        RenderNode node;

        std::getline(HTMLDocument, line);

        if (line.empty())
        {
            throw 1;
        }

        while (!HTMLDocument.eof())
        {
            node.appendText(&line);
            std::getline(HTMLDocument, line);
        }

        Painter display;
        display.paintNode(&node);
        HTMLDocument.close();
    }

    catch (int i)
    {
        if (i == 0)
        {
            std::cerr << "Error: Could not open the document." << std::endl;
        }

        if (i == 1)
        {
            std::cerr << "Error: Document is empty." << std::endl;
        }

    }

}
