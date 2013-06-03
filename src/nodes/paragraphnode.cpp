#include <iostream>
#include <string>
#include "paragraphnode.h"

ParagraphNode::ParagraphNode()
{
    textCharacterSize = 12;
    setNeedsPainting(true);
    setTypeOfNode("p");
}

void ParagraphNode::setText(std::string textToSet)
{
    text = textToSet;
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

/*
void TextNode::paintNode()
{
    std::cout << text << std::endl << std::endl;
}
*/
