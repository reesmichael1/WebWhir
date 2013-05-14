#include <iostream>
#include "textnode.h"

TextNode::TextNode()
{
    textCharacterSize = 12;
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

std::string TextNode::getText()
{
    return text;
}
