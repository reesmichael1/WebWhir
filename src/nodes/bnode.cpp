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
