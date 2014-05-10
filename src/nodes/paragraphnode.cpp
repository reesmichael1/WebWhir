#include "paragraphnode.h"
#include "textnode.h"
#include "painter/paint_nodes/ParagraphPaintNode.h"

ParagraphNode::ParagraphNode()
{
    setNeedsPainting(true);
    setTypeOfRenderNode("p");
}

void ParagraphNode::addText(std::string textToSet)
{
    TextNode* textNode = new TextNode(textToSet);
    childNodes->push_back(textNode);
}

std::string ParagraphNode::getText()
{
    std::string text;

    for (std::vector<RenderNode*>::iterator i = childNodes->begin();
         i != childNodes->end(); i++)
    {
        if (!(*i)->getText().empty())
        {
            text.append((*i)->getText());
        }
    }

    return text;
}

PaintNode* ParagraphNode::convertToPaintNode()
{
    ParagraphPaintNode *paintNode = new ParagraphPaintNode;
    paintNode->addChildPaintNodes(convertChildNodesToPaintNodes());

    return paintNode;
}
