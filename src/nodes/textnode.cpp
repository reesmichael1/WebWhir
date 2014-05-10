#include "textnode.h"
#include "painter/paint_nodes/TextPaintNode.h"

TextNode::TextNode(std::string textToSet)
{
    text = textToSet;
}

std::string TextNode::getText()
{
    return text;
}

PaintNode* TextNode::convertToPaintNode()
{
    PaintNode *textPaintNode = new TextPaintNode(text);
    return textPaintNode;
}
