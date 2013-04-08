#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <string>
#include "SFML/Graphics.hpp"

class RenderNode
{
public:
    RenderNode();
    void setBackgroundColorOfNode(sf::Color colorToSet);
    sf::Color getBackgroundColorOfNode();

private:
    sf::Color backgroundColor;
};

#endif // RENDERNODE_H
