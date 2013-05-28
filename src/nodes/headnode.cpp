#include "headnode.h"

HeadNode::HeadNode()
{
    setNeedsPainting(true);
    setTypeOfNode("head");
}

void HeadNode::paintNode()
{
    setNeedsPainting(false);
}
