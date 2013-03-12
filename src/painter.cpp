#include <iostream>
#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics.hpp"
#include "painter.h"

Painter::Painter(RenderNode *node)
{
    try
    {
        sf::RenderWindow window(sf::VideoMode(800, 600, 32), "OpenWeb");

        while (window.isOpen())
        {
            sf::Font font;

            if (!font.loadFromFile("fonts/Timeless-Bold.ttf"))
            {
                throw "Error: Could not load the font.";
            }

            sf::Text text;
            text.setColor(sf::Color(255,255,255));
            text.setString(node->getText());
            text.setCharacterSize(15);
            window.draw(text);
            window.display();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (sf::Event::Closed == event.type)
                {
                    window.close();
                }
            }
            window.clear();
        }

    }
    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}

void Painter::paintNode(RenderNode *node)
{
    try
    {
        std::cout << node->getText() << std::endl;
        if (node->getText().empty())
        {
            throw "Error: The text was not parsed correctly.";
        }
    }
    catch (char error[])
    {
        std::cerr << error << std::endl;
    }
}
