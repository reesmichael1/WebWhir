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

        std::string line = "Error: no text.";
        RenderNode node;

        while (!line.empty())
        {
            std::getline(HTMLDocument, line);
            if (!line.empty())
            {
                node.appendText(&line);
            }
        }

        Painter::paintNode(&node);
        HTMLDocument.close();
    }

    catch (int i)
    {
        if (i == 0)
        {
            std::cerr << "Error: Could not open the document." << std::endl;
        }
    }

}
