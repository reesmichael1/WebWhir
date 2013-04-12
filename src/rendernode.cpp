#include <iostream>
#include <string>
#include "rendernode.h"

RenderNode::RenderNode()
{
    needsPainting = true;
    backgroundColor = sf::Color::Black;
}

void RenderNode::setBackgroundColorOfNode(sf::Color colorToSet)
{
    backgroundColor = colorToSet;
}

std::string RenderNode::getText()
{
    return NULL;
}

sf::Color RenderNode::getBackgroundColorOfNode()
{
    return backgroundColor;
}
