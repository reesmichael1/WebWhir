#ifndef HTMLBODYELEMENT_H
#define HTMLBODYELEMENT_H

#include "elements/HTMLElement.h"

class HTMLBodyElement : public HTMLElement
{
public:
    HTMLBodyElement();
    virtual RenderNode *returnNode();
};

#endif // HTMLBODYELEMENT_H
