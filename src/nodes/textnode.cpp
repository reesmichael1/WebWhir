#include <iostream>
#include <string>
#include "textnode.h"

TextNode::TextNode()
{
    textCharacterSize = 12;
    setNeedsPainting(true);
}

void TextNode::setText(std::string textToSet)
{
    text = textToSet;
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
    setNeedsPainting(false);
}
