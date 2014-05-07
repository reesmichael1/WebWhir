#include "paragraphnode.h"
#include "painter/paint_nodes/ParagraphPaintNode.h"

ParagraphNode::ParagraphNode()
{
    setNeedsPainting(true);
    setTypeOfRenderNode("p");
}

PaintNode* ParagraphNode::convertToPaintNode()
{
    ParagraphPaintNode *paintNode = new ParagraphPaintNode;
    paintNode->setText(getText());

    return paintNode;
}
