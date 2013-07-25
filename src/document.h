#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "nodes/rendernode.h"

class RenderNode;

class Document
{
public:
    Document();
    ~Document();
    void constructTree(RenderNode *childNode, RenderNode *parentNode);
    RenderNode *getFirstNode();

private:
    RenderNode *firstNode;
};

#endif // DOCUMENT_H
