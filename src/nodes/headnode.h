#ifndef HEADNODE_H
#define HEADNODE_H

#include "rendernode.h"

class HeadNode : public RenderNode
{
public:
    HeadNode();
    virtual void paintNode();
};

#endif // HEADNODE_H
