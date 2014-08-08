#include "painter/wwPainter/wwpainter.h"

#include "ParagraphPaintNode.h"

ParagraphPaintNode::ParagraphPaintNode()
{
    text = "";
}

void ParagraphPaintNode::setText(std::string textToSet)
{
    text = textToSet;
}

std::string ParagraphPaintNode::getText()
{
    return text;
}

void ParagraphPaintNode::paint(WWPainter *wwPainter, PaintArea *display,
                               Layout *layout)
{
    for (std::vector<PaintNode*>::iterator i = getChildPaintNodes().begin() + 1;
         i != getChildPaintNodes().end(); i++)
    {
        (*i)->setIsInline(true);
    }
    paintChildNodes(wwPainter, display, layout);
}
