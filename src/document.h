#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "nodes/rendernode.h"

class Document
{
public:
    Document();
    void constructTree(RenderNode *nodeToAdd);
    void paintWebpage();

private:
    RenderNode *firstNode;
};

#endif // DOCUMENT_H
