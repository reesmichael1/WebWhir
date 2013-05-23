#include "HTMLBodyElement.h"
#include "nodes/rendernode.h"
#include "nodes/bodynode.h"

HTMLBodyElement::HTMLBodyElement()
{
}

RenderNode* HTMLBodyElement::returnNode()
{
    BodyNode bodyNode;
    RenderNode *body = &bodyNode;
    return body;
}
