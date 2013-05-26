#include "headnode.h"

HeadNode::HeadNode()
{
    setNeedsPainting(true);
}

void HeadNode::paintNode()
{
    setNeedsPainting(false);
}
