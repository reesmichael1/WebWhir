#include "HTMLBodyElement.h"
#include "nodes/rendernode.h"
#include "nodes/bodynode.h"

HTMLBodyElement::HTMLBodyElement()
{
}

RenderNode* HTMLBodyElement::returnNode()
{
    BodyNode *bodyNode = new BodyNode;
    RenderNode *body = new RenderNode;
    body = bodyNode;
    body->setChildNode(NULL);
    return body;
}
