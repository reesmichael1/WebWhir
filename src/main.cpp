#include <iostream>
#include <fstream>
#include <stdio.h>
#include "htmlreader.h"

int main(int argc, char* argv[])
{

    if (argc > 1)
    {
        HTMLReader::parseDocument(argv[1]);
    }

    else
    {
        std::cout << "Please enter the filepath of the HTML Document." << std::endl;
        char HTMLFilepath[256];
        std::cin >> HTMLFilepath;

        HTMLReader::parseDocument(HTMLFilepath);
    }

    return 0;
}
