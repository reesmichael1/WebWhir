#include <iostream>
#include <string>
#include "textnode.h"

TextNode::TextNode()
{
    textCharacterSize = 12;
    setNeedsPainting(true);
    setTypeOfNode("p");
}

void TextNode::setText(std::string textToSet)
{
    text = textToSet;
}

std::string TextNode::getText()
{
    return text;
}

void TextNode::setTextCharacterSize(int size)
{
    textCharacterSize = size;
}

int TextNode::getTextCharacterSize()
{
    return textCharacterSize;
}

void TextNode::paintNode()
{
    std::cout << text << std::endl << std::endl;
}
