#include <iostream>
#include <string>
#include "painter.h"
#include "SDL/SDL.h"

Painter::Painter()
{
    try
    {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw 0;
    }

    renderScreen = NULL;
    renderScreen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (renderScreen == NULL)
    {
        throw 0;
    }
    }
    catch (int i)
    {
        if (i == 0)
        {
            std::cout << "Error: Could not initialize SDL." << std::endl;
        }
    }
}

void Painter::paintNode(RenderNode *node)
{
    std::cout << node->getText() << std::endl;

    //An extremely obnoxious hack I have to put in to be
    //able to work on Windows (even though most of my
    //development time is spent on Mac OS X/Linux).
    char pause;
    std::cin >> pause;

    SDL_Quit();
}
