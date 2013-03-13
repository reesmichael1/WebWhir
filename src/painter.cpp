#include <iostream>
#include <string>
#include "STRTK/strtk.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics.hpp"
#include "painter.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

Painter::Painter(RenderNode *node)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "OpenWeb");
    paintNode(node, &window);
}

//SFML does not automatically wrap text to fit the window. This is a hurriedly
//implemented, temporary solution, and will receive more attention in the future.
std::string Painter::parseTextToLines(std::string textToParse, int windowBoundary)
{
    std::vector<std::string> wordVector;

    strtk::parse(textToParse, " ", wordVector);

    std::string parsedString;
    std::string temporaryString;
    sf::Text tempString;

    for (int i = 0; i < wordVector.size(); i++)
    {
        temporaryString = temporaryString + wordVector.at(i) + "\n";
        tempString.setString(temporaryString);
        if (!tempString.getLocalBounds().width)
        {
            parsedString = parsedString + wordVector.at(i) + " ";
        }
        else
        {
            parsedString += "\n";
        }
    }

    return parsedString;
}


void Painter::paintNode(RenderNode *node, sf::RenderWindow *window)
{
    try
    {
        sf::Text text;


        text.setString(parseTextToLines(node->getText(), WINDOW_WIDTH));
        text.setCharacterSize(15);

        sf::Font font;
        if (!font.loadFromFile("fonts/LinLibertine_R.ttf"))
        {
            throw "Error: Could not load the font.";
        }

        text.setFont(font);

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
