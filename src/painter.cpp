#include <iostream>
#include <string>
#include "SFML/Window.hpp"
#include "painter.h"

Painter::Painter(RenderNode *node)
{
    sf::Window window(sf::VideoMode(800,600), "OpenWeb", sf::Style::Default);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}

void Painter::paintNode(RenderNode *node)
{
    try
    {
        std::cout << node->getText() << std::endl;
        if (node->getText().empty())
        {
            throw "Error: Empty text.";
        }
    }
    catch (char error[])
    {
        std::cerr << error << std::endl;
    }
}
