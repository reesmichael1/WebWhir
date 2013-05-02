#include <iostream>
#include <string>
#include <vector>
#include "STRTK/strtk.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "rendernode.h"
#include "painter.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define LEFT_BORDER 10
#define TOP_BORDER 10

Painter::Painter()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,
                                                WINDOW_HEIGHT, 32), "OpenWeb");
}

Painter::~Painter()
{
    delete window;
}

std::string Painter::appendText(std::string textToSet, std::string text)
{
    if (!text.empty())
    {
        std::string oldText = text;
        text = oldText + "\n" + textToSet;
    }

    else
    {
        text = textToSet;
    }

    return text;
}

//SFML does not automatically wrap text to fit the window. This is a hurriedly
//implemented, temporary solution, and will receive more attention in the future.
//Right now, I am considering adopting SFGUI as an additional graphics library
//to address this (and other) issues I have found with SFML.
std::string Painter::parseTextToLines(std::string textToParse,
                                      int textCharacterSize, int windowBoundary)
{
    std::vector<std::string> wordVector;

    strtk::parse(textToParse, " ", wordVector);

    std::string parsedString;
    std::string temporaryString;

    for (unsigned int i = 0; i < wordVector.size(); i++)
    {
        temporaryString = temporaryString + wordVector.at(i) + " ";

        if (temporaryString.size() * textCharacterSize < windowBoundary)
        {
            parsedString = parsedString + wordVector.at(i) + " ";
        }
        else
        {
            parsedString = parsedString + "\n" + wordVector.at(i) + " ";
            temporaryString.clear();
        }
    }

    return parsedString;
}


void Painter::paintNodes()
{
    try
    {

        sf::Font font;

        if (!font.loadFromFile("fonts/DejaVuSans.ttf"))
        {
            throw "Error: Could not load font.";
        }

        sf::View mainView = window->getDefaultView();

        sf::Text mainText;

        //I hate to do this, but I'm running out of other options.
        //This is the easiest way to keep the text on the screen.
        //It strikes me as too hackish, so I'll keep working on it.
        int downKeyPush = 0;

        std::string temporaryString = "This string is temporary.";

        mainText.setFont(font);
        mainText.setCharacterSize(18);
        mainText.setString(temporaryString);

        while (window->isOpen())
        {
            sf::Event event;

            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }

                //Someday, this line will include a comparison of time to
                //account for different hardware spees.
                float Offset = 100.f;

                if (event.type == sf::Event::KeyPressed)
                {

                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up :
                    {
                        if (downKeyPush > 0)
                        {
                            mainView.move(0, -Offset);
                            downKeyPush--;
                        }
                        break;
                    }
                    case sf::Keyboard::Down :
                    {
                        mainView.setCenter(mainView.getCenter().x,
                                           mainView.getCenter().y + Offset);
                        downKeyPush++;
                        break;
                    }
                    case sf::Keyboard::Escape :
                    {
                        window->close();
                        break;
                    }
                    }
                }

                if (event.type == sf::Event::Resized)
                {
                    mainView.setSize(static_cast<float>(window->getSize().x),
                                     static_cast<float>(window->getSize().y));
                    window->setView(mainView);
                }

            }

            window->setView(mainView);
            window->clear();
            window->draw(mainText);
            window->display();

            sf::sleep(sf::milliseconds(10));
        }

    }
    catch (char error[])
    {
        std::cout << error << std::endl;
    }
}

