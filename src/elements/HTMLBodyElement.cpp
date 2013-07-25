#include "HTMLBodyElement.h"
#include "nodes/rendernode.h"
#include "nodes/bodynode.h"

HTMLBodyElement::HTMLBodyElement()
{
}

BodyNode* HTMLBodyElement::returnNode()
{
    bodyNode = new BodyNode;

    return bodyNode;
}
