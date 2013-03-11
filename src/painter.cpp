#include <iostream>
#include <string>
#include "painter.h"

Painter::Painter(RenderNode *node)
{

}

void Painter::paintNode(RenderNode *node)
{
    try
    {
        std::cout << node->getText() << std::endl;
        if (node->getText().empty())
        {
            throw "Error: Empty text.";
        }
    }
    catch (char error[])
    {
        std::cerr << error << std::endl;
    }
}
