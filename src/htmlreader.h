#ifndef HTMLREADER_H
#define HTMLREADER_H

#include <fstream>

class HTMLReader
{
public:
    HTMLReader();
    static void parseDocument(char HTMLFilepath[]);
};

#endif // HTMLREADER_H
