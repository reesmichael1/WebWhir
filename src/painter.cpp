#include <iostream>
#include <string>
#include "painter.h"
#include "SDL/SDL.h"

Painter::Painter()
{
}

void Painter::paintNode(RenderNode *node)
{
    std::cout << node->getText() << std::endl;
}

void Painter::drawScreen()
{
}
