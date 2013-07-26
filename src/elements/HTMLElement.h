#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

//Right now, HTML elements serve basically no purpose within WebWhirr.
//However, once inline attributes are added in version 0.2, their importance
//will grow significantly.

#include <string>
#include "nodes/rendernode.h"

class HTMLElement
{
public:
    virtual RenderNode* returnNode() = 0;
};

#endif // HTMLELEMENT_H
