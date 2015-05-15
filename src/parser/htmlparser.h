#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class HTMLParser
{
public:
    HTMLParser();
    bool validateHTML(std::string htmlString);

private:
    bool hasDoctype(std::string htmlString);
    bool hasRootElement(std::string htmlString);

    enum insertionMode {
        initial,
        beforeHtml,
        beforeHead,
        inHead,
        inHeadNoScript,
        afterHead,
        inBody,
        text,
        inTable,
        inTableText,
        inCaption,
        inColumnGroup,
        inTableBody,
        inRow,
        inCell,
        inSelect,
        inSelectInTable,
        afterBody,
        inFrameset,
        afterFrameset,
        afterAfterBody,
        afterAfterFrameset,
    };

    // Will eventually become pointers to RenderNodes
    std::vector<std::string> openElementsStack;
    insertionMode resetInsertionMode();
};

#endif // PARSER_H
