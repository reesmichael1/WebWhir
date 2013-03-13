#include <iostream>
#include <string>
#include "SFML/System.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics.hpp"
#include "painter.h"

Painter::Painter(RenderNode *node)
{

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "OpenWeb");
    paintNode(node, &window);
}


void Painter::paintNode(RenderNode *node, sf::RenderWindow *window)
{
    try
    {

        sf::Text text(node->getText());
        while (window->isOpen())
        {
            window->clear();
            window->draw(text);
            window->display();

            sf::Event event;
            while (window->pollEvent(event))
            {
                if (sf::Event::Closed == event.type)
                {
                    window->close();
                }
            }
        }
    }

    catch (std::string error)
    {
        std::cout << error << std::endl;
    }
}
