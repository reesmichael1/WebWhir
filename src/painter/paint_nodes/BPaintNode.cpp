#include "BPaintNode.h"

BPaintNode::BPaintNode()
{
}

void BPaintNode::paint(WWPainter *wwPainter, PaintArea *display,
                               Layout *layout)
{
    for (PaintNode* childPaintNode : this->getChildPaintNodes())
    {
        childPaintNode->addPaintOption(boldText);
    }
    paintChildNodes(wwPainter, display, layout);
}
