#ifndef PAINTER_H
#define PAINTER_H

#include "SDL/SDL.h"
#include "rendernode.h"

class Painter
{
public:
    Painter(RenderNode *node);
    void paintNode(RenderNode *node);

private:
    SDL_Surface *renderScreen;
};

#endif // PAINTER_H
