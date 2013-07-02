#include <iostream>
#include <string>
#include "paragraphnode.h"

ParagraphNode::ParagraphNode()
{
    textCharacterSize = 12;
    setNeedsPainting(true);
    setTypeOfNode("p");
}

void ParagraphNode::addCharacter(std::string::iterator i)
{
    text.append(1, i[0]);
}

std::string ParagraphNode::getText()
{
    return text;
}

void ParagraphNode::setTextCharacterSize(int size)
{
    textCharacterSize = size;
}

int ParagraphNode::getTextCharacterSize()
{
    return textCharacterSize;
}

