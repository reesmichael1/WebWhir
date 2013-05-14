#include <iostream>
#include <string>
#include <fstream>
#include "parser/htmlreader.h"

int main(int argc, char* argv[])
{

    std::string HTMLFilepath;

    if (argc > 1)
    {
        HTMLFilepath = argv[1];
    }

    else
    {
        std::cout << "Please enter the filepath of the HTML Document." << std::endl;
        std::cin >> HTMLFilepath;

    }

    HTMLReader reader;
    reader.prepareDocument(HTMLFilepath);

    return 0;
}
