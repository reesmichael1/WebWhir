#include <iostream>
#include <string>
#include "painter.h"
#include "SDL/SDL.h"

Painter::Painter()
{
}

void Painter::paintNode(RenderNode *node)
{

        SDL_Init(SDL_INIT_VIDEO);
        std::cout << node->getText() << std::endl;

        SDL_Quit();

}

void Painter::drawScreen()
{
    SDL_Surface *screen;

    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
}
