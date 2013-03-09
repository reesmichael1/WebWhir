#include <iostream>
#include <string>
#include "rendernode.h"

RenderNode::RenderNode()
{
}

void RenderNode::appendText(std::string *textToSet)
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

std::string RenderNode::getText()
{
    return text;
}
