#include "renderobject.h"

RenderObject::RenderObject()
{
}

void RenderObject::setText(std::string textString)
{
    text = textString;
}

std::string RenderObject::getText()
{
    return text;
}
