#include <iostream>
#include "bnode.h"

BNode::BNode()
{
    setNeedsPainting(true);
    setTypeOfNode("b");
}

void BNode::paintNode(std::string *webpageString)
{
    std::string temporaryString = text + "\n\n";
    *webpageString += temporaryString;
}

void BNode::addCharacter(std::string::iterator i)
{
    text.append(1, i[0]);
}

std::string BNode::getText()
{
    return text;
}
