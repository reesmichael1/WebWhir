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
            throw "Error: Could not open document.";
        }

        std::string line;
        RenderNode node;

        std::getline(HTMLDocument, line);

        if (line.empty())
        {
            throw "Error: Document is empty.";
        }

        while (!HTMLDocument.eof())
        {
            node.appendText(&line);
            std::getline(HTMLDocument, line);
        }

        Painter display(&node);
        //Painter::paintNode(&node);
        HTMLDocument.close();
    }

    catch (char error[])
    {
        std::cerr << error << std::endl;
    }

}
