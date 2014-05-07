#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "nodes/rendernode.h"

class RenderNode;

class Document
{
public:
    Document();
    ~Document();
    void constructTree(RenderNode *childNode, RenderNode *parentNode);
    void clearTree();
    RenderNode *getFirstNode();
    void setDocumentTitle(std::string titleToSet);
    std::string getDocumentTitle();

private:
    RenderNode *firstNode;
    std::string documentTitle;
};

#endif // DOCUMENT_H
