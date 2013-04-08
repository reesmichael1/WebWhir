#ifndef COLOROPERATIONS_H
#define COLOROPERATIONS_H

#include "SFML/Graphics.hpp"

class ColorOperations
{
public:
    ColorOperations();
    static sf::Color convertStringToColor(std::string colorString);
};

#endif // COLOROPERATIONS_H
