#include "bodynode.h"

BodyNode::BodyNode()
{
    setNeedsPainting(true);
    setTypeOfNode("body");
}

void BodyNode::paintNode()
{
    setNeedsPainting(false);
}
