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


void ParagraphNode::paintNode(std::string *webpageString)
{
    std::string temporaryString = text + "\n\n";
    *webpageString += temporaryString;
}

