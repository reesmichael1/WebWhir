#ifndef HTMLREADER_H
#define HTMLREADER_H

#include <fstream>
#include "coloroperations.h"
#include "document.h"

class HTMLReader : protected ColorOperations
{
public:
    HTMLReader();
    ~HTMLReader();
    void prepareDocument(char HTMLFilepath[]);
    void parseDocumentTags(std::string textToParse);
    void parseTagsIntoNodes();

private:
    Document *webpage;
};

#endif // HTMLREADER_H
