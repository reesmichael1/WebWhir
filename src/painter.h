#ifndef PAINTER_H
#define PAINTER_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"
#include "textnode.h"

class Painter
{
public:
    Painter();
    void paintNodes();

private:
    static std::string parseTextToLines(std::string textToParse, int textCharacterSize, int windowBoundary);
    std::string appendText(std::string textToSet, std::string text);
    sf::RenderWindow *window;

};

#endif // PAINTER_H
