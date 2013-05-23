#ifndef HTMLPELEMENT_H
#define HTMLPELEMENT_H

#include "HTMLElement.h"

class HTMLPElement : HTMLElement
{
public:
    HTMLPElement();
    virtual RenderNode *returnNode();
};

#endif // HTMLPELEMENT_H
