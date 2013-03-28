#include <iostream>
#include <string>
#include "STRTK/strtk.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "painter.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define LEFT_BORDER 10
#define TOP_BORDER 10

Painter::Painter(RenderNode *node)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "OpenWeb");
    paintNode(node, &window);

    //tgui::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "OpenWeb");
    //paintNode(node, &window);
}

//SFML does not automatically wrap text to fit the window. This is a hurriedly
//implemented, temporary solution, and will receive more attention in the future.
//Right now, I am considering adopting SFGUI as an additional graphics library
//to address this (and other) issues I have found with SFML.
std::string Painter::parseTextToLines(std::string textToParse, int windowBoundary)
{
    std::vector<std::string> wordVector;

    strtk::parse(textToParse, " ", wordVector);

    std::string parsedString;
    std::string temporaryString;
    sf::Text tempString;

    for (unsigned int i = 0; i < wordVector.size(); i++)
    {
        temporaryString = temporaryString + wordVector.at(i) + " ";
        tempString.setString(temporaryString);

        if (tempString.getLocalBounds().width < windowBoundary)
        {
            parsedString = parsedString + wordVector.at(i) + " ";
        }
        else
        {
            parsedString = parsedString + "\n" + wordVector.at(i) + " ";
            tempString.setString("");
            temporaryString.clear();
        }
    }

    return parsedString;
}


void Painter::paintNode(RenderNode *node, sf::RenderWindow *window)
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
        int rightKeyPush = 0;
        int downKeyPush = 0;

        //The second parameter is here to fix the issue with the text wrapping function on Linux,
        //where the width of the sf::Rect that bounds the text is not properly defined.
        //This is a magic number, and is here temporarily because it works.
        mainText.setString(parseTextToLines(node->getText(), WINDOW_WIDTH));
        mainText.setFont(font);
        mainText.setCharacterSize(12);
        mainText.setPosition(LEFT_BORDER, TOP_BORDER);

        while (window->isOpen())
        {
            sf::Event event;

            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }

                //Someday, this line will include a comparison of time to account for different hardware spees.
                float Offset = 200.f;

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
                        mainView.setCenter(mainView.getCenter().x, mainView.getCenter().y + Offset);
                        downKeyPush++;
                        break;
                    }
                    case sf::Keyboard::Left :
                    {
                        if (rightKeyPush > 0)
                        {
                            mainView.move(-Offset, 0);
                            rightKeyPush--;
                        }
                        break;
                    }
\
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
