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

void ParagraphPaintNode::paint(WWPainter &wwPainter, PaintArea *display,
                               Layout *layout)
{
    for (size_t i = 0; i < childPaintNodes.size(); i++)
    {
        childPaintNodes.at(i)->setIsInline(true);
    }
    paintChildNodes(wwPainter, display, layout);
}

void ParagraphPaintNode::setIsInline(bool inlineOrNot)
{
    this->setIsInline(inlineOrNot);
    for (PaintNode* childPaintNode : childPaintNodes)
    {
        childPaintNode->setIsInline(inlineOrNot);
    }
}
