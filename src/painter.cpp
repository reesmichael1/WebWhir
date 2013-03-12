#include <iostream>
#include <string>
#include "painter.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

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

        TTF_Font *typeFont = NULL;
        typeFont = TTF_OpenFont("fonts/tunga.ttf", 100);

        if (typeFont == NULL)
        {
            throw "Error: Could not initialize the font library.";
        }

        SDL_Surface *tempScreen = NULL;
        SDL_Surface *returnScreen = NULL;

        SDL_Color textColor;
        textColor.b = 100;
        textColor.g = 100;
        textColor.r = 100;

        tempScreen = (TTF_RenderText_Blended(typeFont,
                                             node->getText().c_str(), textColor));

        if(tempScreen == NULL)
        {
            throw "Error: Could not render the text properly.";
        }

        returnScreen = SDL_DisplayFormat(tempScreen);
        SDL_FreeSurface(tempScreen);

        if (returnScreen == NULL)
        {
            throw "Error: Could not write the fonts properly.";
        }

        SDL_Rect rectangle;

        rectangle.x = 0;
        rectangle.y = 0;

        SDL_BlitSurface(returnScreen, NULL, renderScreen, &rectangle);

        TTF_Quit();

    }
    catch (char error[])
    {
        std::cerr << error << std::endl;
    }
}
