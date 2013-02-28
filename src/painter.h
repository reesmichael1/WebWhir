#ifndef PAINTER_H
#define PAINTER_H

#include "renderobject.h"

class Painter
{
public:
    Painter();
    static void drawNode(RenderObject* node);
};

#endif // PAINTER_H
