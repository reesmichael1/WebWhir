#include "paintnode.h"

PaintNode::PaintNode(const char c, Painter *painterToAdd)
{
    character = new char;
    *character = c;
    node = NULL;

    painter = painterToAdd;
}

PaintNode::PaintNode(RenderNode *nodeToAdd, Painter *painterToAdd)
{
    node = new RenderNode;
    node = nodeToAdd;

    character = NULL;

    painter = painterToAdd;
}

PaintNode::~PaintNode()
{
    delete character;
    delete node;
}

void PaintNode::paint(QFont::Weight weight)
{
    if (node)
    {
        node->paintNode();
    }

    else
    {
        painter->addCharacter(*character, weight);
    }
}
