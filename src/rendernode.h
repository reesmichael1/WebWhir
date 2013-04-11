#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <string>
#include "SFML/Graphics.hpp"

class RenderNode
{
public:
    RenderNode();
    virtual void setBackgroundColorOfNode(sf::Color colorToSet);
    virtual sf::Color getBackgroundColorOfNode();
    virtual std::string getText();

private:
    sf::Color backgroundColor;
};

#endif // RENDERNODE_H
