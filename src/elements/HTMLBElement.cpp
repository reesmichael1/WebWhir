#include "HTMLBElement.h"
#include "nodes/rendernode.h"
#include "nodes/bnode.h"

HTMLBElement::HTMLBElement()
{
}

BNode* HTMLBElement::returnNode()
{
    bNode = new BNode;

    return bNode;
}

