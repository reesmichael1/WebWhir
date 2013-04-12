#include <iostream>
#include <fstream>
#include <stdio.h>
#include "htmlreader.h"

int main(int argc, char* argv[])
{

    HTMLReader reader;
    if (argc > 1)
    {
        reader.prepareDocument(argv[1]);
    }

    else
    {
        std::cout << "Please enter the filepath of the HTML Document." << std::endl;
        char HTMLFilepath[256];
        std::cin >> HTMLFilepath;

        reader.prepareDocument(HTMLFilepath);
    }

    return 0;
}
