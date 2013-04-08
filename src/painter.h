#ifndef PAINTER_H
#define PAINTER_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"
#include "textnode.h"

class Painter
{
public:
    Painter(TextNode *node);
    static void paintText(TextNode *node, sf::RenderWindow *window);

private:
    static std::string parseTextToLines(std::string textToParse, int textCharacterSize, int windowBoundary);

};

#endif // PAINTER_H
