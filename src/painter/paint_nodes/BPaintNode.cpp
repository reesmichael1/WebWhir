#include "BPaintNode.h"

BPaintNode::BPaintNode()
{
}

void BPaintNode::paint(WWPainter *wwPainter, PaintArea *display,
                               Layout *layout)
{
    for (PaintNode* childPaintNode : this->getChildPaintNodes())
    {
        if (isInlineNode())
        {
            childPaintNode->setIsInline(true);
        }
        childPaintNode->addPaintOption(boldText);
    }
    paintChildNodes(wwPainter, display, layout);
}
