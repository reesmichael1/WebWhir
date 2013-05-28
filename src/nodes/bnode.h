#ifndef BNODE_H
#define BNODE_H

#include <string>
#include "nodes/textnode.h"

class BNode : public TextNode
{
public:
    BNode();
    virtual void paintNode();
};

#endif // BNODE_H
