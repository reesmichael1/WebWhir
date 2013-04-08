#include <iostream>
#include "textnode.h"

TextNode::TextNode()
{
    textCharacterColor = sf::Color::White;
    textCharacterSize = 12;
}

void TextNode::appendText(std::string *textToSet)
{
    if (!text.empty())
    {
        std::string oldText = text;
        text = oldText + "\n" + *textToSet;
    }

    else
    {
        text = *textToSet;
    }
}

sf::Color TextNode::getCharacterColor()
{
    return textCharacterColor;
}

void TextNode::setCharacterColor(sf::Color colorToSet)
{
    textCharacterColor = colorToSet;
}

void TextNode::setTextBackgroundColor(sf::Color colorToSet)
{
    textBackgroundColor = colorToSet;
}

sf::Color TextNode::getTextBackgroundColor()
{
    return textBackgroundColor;
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
