#ifndef HTMLREADER_H
#define HTMLREADER_H

#include <string>
#include <fstream>
#include "document.h"

class HTMLReader
{
public:
    HTMLReader();
    ~HTMLReader();
    void paint();
    void prepareDocument(std::string HTMLFilepath);

    //These are defined by the W3C HTML5 parser specification.
    enum parseState {
        initialMode,
        beforeHTML,
        beforeHead,
        inHead,
        inHeadNoscript,
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
        tagOpen,
        endTagOpen,
        tagName,
        endTagName,
        bogusComment,
        doctypeDeclaration
    };

private:
    Document *webpage;
    RenderNode *currentParentNode;
    RenderNode *currentNode;
    void parseDocumentText(std::string documentText);
    bool parentNodeClosed(RenderNode *node, std::string typeOfNode);
};

#endif // HTMLREADER_H
