#ifndef HTMLULELEMENT_H
#define HTMLULELEMENT_H

#include "nodes/ulnode.h"
#include "HTMLElement.h"

class HTMLUlElement : HTMLElement
{
public:
    HTMLUlElement();
    virtual UlNode* returnNode();

private:
    UlNode *ulNode;
};

#endif // HTMLULELEMENT_H
