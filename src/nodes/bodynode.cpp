#include "bodynode.h"

BodyNode::BodyNode()
{
    setNeedsPainting(true);
}

void BodyNode::paintNode()
{
    setNeedsPainting(false);
}
