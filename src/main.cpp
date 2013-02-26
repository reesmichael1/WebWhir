#include <iostream>
#include <fstream>
#include <stdio.h>
#include "htmlreader.h"

int main(int argc, char* argv[])
{

    FILE *HTMLDocument;
    HTMLDocument = fopen(argv[1], "r");

    HTMLReader::parseDocument(HTMLDocument);

    return 0;
}
