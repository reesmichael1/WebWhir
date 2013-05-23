#ifndef HTMLBODYELEMENT_H
#define HTMLBODYELEMENT_H

#include "nodes/bodynode.h"
#include "elements/HTMLElement.h"

class HTMLBodyElement : public HTMLElement
{
public:
    HTMLBodyElement();
    virtual RenderNode *returnNode();
};

#endif // HTMLBODYELEMENT_H
