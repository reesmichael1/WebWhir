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
#include "nodes/inode.h"
#include "nodes/imagenode.h"
#include "nodes/horizontalrulenode.h"
#include "nodes/listnode.h"
#include "nodes/ulnode.h"

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
    //They are uncommented as support for the tag is added.
    enum parseState {
        initialMode,
        //beforeHTML,
        //beforeHead,
        //inHead,
        //inHeadNoscript,
        //afterHead,
        //inBody,
        text,
        //inTable,
        //inTableText,
        //inCaption,
        //inColumnGroup,
        //inTableBody,
        //inRow,
        //inCell,
        //inSelect,
        //inSelectInTable,
        //afterBody,
        //inFrameset,
        //afterFrameset,
        //afterAfterBody,
        //afterAfterFrameset,
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
                           parseState &currentState, std::string::iterator &i, std::string HTMLFilepath);
    ParagraphNode* createParagraphNode(parseState &currentState);
    BNode* createBNode(parseState &currentState);
    INode* createINode(parseState &currentState);
    ImageNode *createImageNode(parseState &currentState,
                               std::string::iterator &i, std::string HTMLFilepath);
    HorizontalRuleNode *createHrNode();
    ListNode *createLiNode(parseState &currentState);
    UlNode *createUlNode();
    void initialModeCase(parseState &currentState, std::string::iterator &i);
    void tagOpenCase(parseState &currentState, std::string::iterator &i);
    void tagNameCase(parseState &currentState, std::string::iterator &i, std::string HTMLFilepath);
    Document *endTagNameCase(parseState &currentState, std::string::iterator &i);
    void endTagOpenCase(parseState &currentState, std::string::iterator &i);
    void bogusCommentCase(parseState &currentState, std::string::iterator &i);
    void doctypeDeclarationCase(parseState &currentState, std::string::iterator &i);
    void textCase(parseState &currentState, std::string::iterator &i);

private:
    Document *webpage;
    RenderNode *currentParentNode;
    RenderNode *currentNode;
    Document* parseDocumentText(std::string documentText, std::string HTMLFilepath);
    bool parentNodeClosed(RenderNode *node, std::string typeOfNode);
    std::string getTagString(std::string::iterator &i, parseState &currentState);
};

#endif // HTMLREADER_H
