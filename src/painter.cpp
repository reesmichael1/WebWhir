#include <iostream>
#include <string>
#include "painter.h"
#include "SDL/SDL.h"

Painter::Painter(RenderNode *node)
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

        paintNode(node);

        //An extremely obnoxious hack I have to put in to be
        //able to work on Windows (even though most of my
        //development time is spent on Mac OS X/Linux).
        std::cin.get();

        SDL_Quit();
    }

    catch (int i)
    {
        if (i == 0)
        {
            std::cerr << "Error: Could not initialize SDL." << std::endl;
        }
    }
}

void Painter::paintNode(RenderNode *node)
{
    try
    {

        SDL_Surface *tempScreen = NULL;
        SDL_Surface *returnScreen = NULL;

        if((tempScreen = SDL_LoadBMP("bitmap.bmp")) == NULL)
        {
            throw "Error: Could not load the bitmap.";
        }

        returnScreen = SDL_DisplayFormat(tempScreen);
        SDL_FreeSurface(tempScreen);


        SDL_Rect rectangle;

        rectangle.x = 10;
        rectangle.y = 25;

        SDL_BlitSurface(returnScreen, NULL, renderScreen, &rectangle);

    }
    catch (char error[])
    {
        std::cerr << error << std::endl;
    }
}
