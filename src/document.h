#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "rendernode.h"

class Document
{
public:
    Document();
    void constructTree(RenderNode *nodeToAdd);

private:
    RenderNode *firstNode;
};

#endif // DOCUMENT_H
