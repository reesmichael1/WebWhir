#ifndef BNODE_H
#define BNODE_H

#include "nodes/paragraphnode.h"

class BNode : public ParagraphNode
{
public:
    BNode();
    virtual PaintNode* convertToPaintNode();

};

#endif // BNODE_H
