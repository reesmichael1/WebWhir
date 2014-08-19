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
    paintChildNodes(wwPainter, display, layout);
}
