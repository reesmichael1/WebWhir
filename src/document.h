#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <vector>
#include "rendernode.h"

class Document
{
public:
    Document();
    void constructTree(RenderNode *nodeToAdd);

};

#endif // DOCUMENT_H
