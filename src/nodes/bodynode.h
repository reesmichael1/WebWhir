#ifndef BODYNODE_H
#define BODYNODE_H

#include "nodes/rendernode.h"

class BodyNode : public RenderNode
{
public:
    BodyNode();
    virtual void paintNode();
};

#endif // BODYNODE_H
