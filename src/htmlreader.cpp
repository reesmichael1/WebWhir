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
    }

    catch (int i)
    {
        if (i == 0)
        {
            std::cerr << "Error: Could not open the document." << std::endl;
        }
    }
>>>>>>> bb6e85ace0634183f8aa5940903cde59aee0c863
}
