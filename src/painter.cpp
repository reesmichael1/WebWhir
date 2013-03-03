#include "painter.h"
#include <iostream>
#include <string>

Painter::Painter()
{
}

void Painter::paintNode(RenderNode *node)
{
    std::cout << node->getText() << std::endl;
}
