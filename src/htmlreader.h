#ifndef HTMLREADER_H
#define HTMLREADER_H

#include <fstream>
#include "coloroperations.h"

class HTMLReader : protected ColorOperations
{
public:
    HTMLReader();
    static void parseDocument(char HTMLFilepath[]);
};

#endif // HTMLREADER_H
