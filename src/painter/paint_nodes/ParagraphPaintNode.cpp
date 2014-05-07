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
