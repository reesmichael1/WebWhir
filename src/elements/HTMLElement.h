#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include "nodes/rendernode.h"

class HTMLElement
{
public:
    virtual RenderNode* returnNode() = 0;

};

#endif // HTMLELEMENT_H
