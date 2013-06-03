#include <iostream>
#include "bnode.h"

BNode::BNode()
{
    setNeedsPainting(true);
    setTypeOfNode("b");
}

void BNode::setText(std::string textToSet)
{
    text = textToSet;
}

std::string BNode::getText()
{
    return text;
}
