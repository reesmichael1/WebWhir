#include <iostream>
#include <string>
#include "painter.h"
#include "SDL.h"
#include "SDL_ttf.h"

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
        if (TTF_Init() < 0)
        {
            throw "Error: Could not initialize SDL.";
        }

        TTF_Font *tungaFont = NULL;
        tungaFont = TTF_OpenFont("fonts/tunga.ttf", 100);

        if (tungaFont == NULL)
        {
            throw "Error: Could not initialize the font library.";
        }

        SDL_Surface *tempScreen = NULL;
        SDL_Surface *returnScreen = NULL;

        if((tempScreen = SDL_LoadBMP("bitmap.bmp")) == NULL)
        {
            throw "Error: Could not load the bitmap.";
        }

        returnScreen = SDL_DisplayFormat(tempScreen);
        SDL_FreeSurface(tempScreen);

        SDL_Color textColor;
        textColor.b = 100;
        textColor.g = 100;
        textColor.r = 100;
        tempScreen = TTF_RenderText_Blended(tungaFont, node->getText().c_str(), textColor);

        if (returnScreen == NULL)
        {
            throw "Error: Could not write the fonts properly.";
        }

        SDL_Rect rectangle;

        rectangle.x = 10;
        rectangle.y = 25;

        SDL_BlitSurface(returnScreen, NULL, renderScreen, &rectangle);

        TTF_Quit();

    }
    catch (char error[])
    {
        std::cerr << error << std::endl;
    }
}
