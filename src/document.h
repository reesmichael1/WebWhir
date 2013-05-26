#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "nodes/rendernode.h"

class Document
{
public:
    Document();
    ~Document();
    void constructTree(RenderNode *nodeToAdd);
    void paintWebpage();
    RenderNode *getFirstNode();

private:
    RenderNode *firstNode;
};

#endif // DOCUMENT_H
