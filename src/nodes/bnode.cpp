#include <iostream>
#include "bnode.h"

BNode::BNode()
{
    setNeedsPainting(true);
    setTypeOfNode("b");
}

void BNode::addCharacter(std::string::iterator i)
{
    text.append(1, i[0]);
}

std::string BNode::getText()
{
    return text;
}

void BNode::paintNode()
{
    std::vector<PaintNode*>::iterator iterator;
    for (iterator = paintNodes->begin(); iterator != paintNodes->end();
         iterator++)
    {
        (*iterator)->paint(QFont::Bold);
    }
}
