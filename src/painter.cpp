#include <iostream>
#include <string>
#include "SFML/Window.hpp"
#include "painter.h"

Painter::Painter(RenderNode *node)
{
    sf::Window window(sf::VideoMode(800,600), "OpenWeb");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                window.close();
            }
        }
    }

    paintNode(node);
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
