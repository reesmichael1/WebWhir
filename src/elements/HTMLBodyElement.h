#ifndef HTMLBODYELEMENT_H
#define HTMLBODYELEMENT_H

#include "elements/HTMLElement.h"
#include "nodes/bodynode.h"

class HTMLBodyElement : public HTMLElement
{
public:
    HTMLBodyElement();
    virtual RenderNode *returnNode();
    virtual void deleteHTMLElement();

private:
    BodyNode *bodyNode;
    RenderNode *body;
};

#endif // HTMLBODYELEMENT_H
