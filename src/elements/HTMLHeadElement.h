#ifndef HEADELEMENT_H
#define HEADELEMENT_H

#include "HTMLElement.h"

class HTMLHeadElement : public HTMLElement
{
public:

    HTMLHeadElement();
    virtual RenderNode *returnNode();
};

#endif // HEADELEMENT_H
