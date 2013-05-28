#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "nodes/rendernode.h"

class Document
{
public:
    Document();
    ~Document();
    void constructTree(RenderNode *childNode, RenderNode *parentNode);
    void paintWebpage();
    RenderNode *getFirstNode();

private:
    RenderNode *firstNode;
};

#endif // DOCUMENT_H
