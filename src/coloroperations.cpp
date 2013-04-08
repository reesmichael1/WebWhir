#include <iostream>
#include "SFML/Graphics.hpp"
#include "coloroperations.h"

ColorOperations::ColorOperations()
{
}

sf::Color ColorOperations::convertStringToColor(std::string colorString)
{

    if (colorString == "Red")
    {
        return sf::Color::Red;
    }
    else if (colorString == "Blue")
    {
        return sf::Color::Blue;
    }
    else if (colorString == "Black")
    {
        return sf::Color::Black;
    }
    else if (colorString == "White")
    {
        return sf::Color::White;
    }
    else if (colorString == "Purple")
    {
        return sf::Color(0x80, 0x00, 0x80);
    }
    else if (colorString == "LimeGreen")
    {
        return sf::Color(0x32, 0xCD, 0x32);
    }
    else
    {
        std::cout << "Unknown background color: " << colorString << "." << std::endl;
        return sf::Color::White;
    }
}
