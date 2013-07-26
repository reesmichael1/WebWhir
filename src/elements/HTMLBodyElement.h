#ifndef HTMLBODYELEMENT_H
#define HTMLBODYELEMENT_H

#include "elements/HTMLElement.h"
#include "nodes/bodynode.h"

class HTMLBodyElement : public HTMLElement
{
public:
    HTMLBodyElement();
    virtual BodyNode *returnNode();

private:
    BodyNode *bodyNode;
};

#endif // HTMLBODYELEMENT_H
