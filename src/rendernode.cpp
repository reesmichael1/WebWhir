#include "rendernode.h"
#include <iostream>

RenderNode::RenderNode()
{
}

void RenderNode::setText(std::string textToSet)
{
    text = textToSet;
}

std::string RenderNode::getText()
{
    return text;
}
