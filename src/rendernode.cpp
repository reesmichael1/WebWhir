#include <iostream>
#include <string>
#include "rendernode.h"

RenderNode::RenderNode()
{
    backgroundColor = sf::Color::Black;
}

//This will be fixed--I simply wanted to have something to actually see.
void RenderNode::setBackgroundColorOfNode(sf::Color colorToSet)
{
    backgroundColor = colorToSet;
}

sf::Color RenderNode::getBackgroundColorOfNode()
{
    return backgroundColor;
}
