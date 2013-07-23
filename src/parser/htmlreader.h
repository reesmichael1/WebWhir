#ifndef HTMLREADER_H
#define HTMLREADER_H

#include <string>
#include <fstream>
#include "document.h"
#include "nodes/rendernode.h"
#include "nodes/paragraphnode.h"
#include "nodes/headnode.h"
#include "nodes/bodynode.h"
#include "nodes/bnode.h"
#include "painter/painter.h"

class HTMLReader
{
public:
    HTMLReader();
    ~HTMLReader();
    Document *prepareDocument(std::string HTMLFilepath);
    HeadNode *createHeadNode();
    BodyNode* createBodyNode();
    RenderNode* createFirstNode();

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

    std::string returnTagName(std::string::iterator &i,
                              parseState &currentState);
    RenderNode* createNode(std::string nodeName,
                           parseState &currentState);
    ParagraphNode* createParagraphNode(parseState &currentState);
    BNode* createBNode(parseState &currentState);

private:
    Document *webpage;
    RenderNode *currentParentNode;
    RenderNode *currentNode;
    Document* parseDocumentText(std::string documentText);
    bool parentNodeClosed(RenderNode *node, std::string typeOfNode);
};

#endif // HTMLREADER_H
