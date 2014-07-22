#include "BPaintNode.h"

BPaintNode::BPaintNode()
{
}

void BPaintNode::paint(QPainter *qPainter, PaintArea *display,
                               Layout *layout)
{
    for (PaintNode* childPaintNode : this->getChildPaintNodes())
    {
        childPaintNode->addPaintOption(boldText);
    }
    paintChildNodes(qPainter, display, layout);
}
