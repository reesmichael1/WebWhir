#include "HTMLBodyElement.h"
#include "nodes/rendernode.h"
#include "nodes/bodynode.h"

HTMLBodyElement::HTMLBodyElement()
{
}

RenderNode* HTMLBodyElement::returnNode()
{
    bodyNode = new BodyNode;
    body = new RenderNode;
    body = bodyNode;

    return body;
}

void HTMLBodyElement::deleteHTMLElement()
{
    delete bodyNode;
    delete body;
}
