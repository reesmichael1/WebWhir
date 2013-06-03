#include "HTMLBElement.h"
#include "nodes/rendernode.h"
#include "nodes/bnode.h"

HTMLBElement::HTMLBElement()
{
}

RenderNode* HTMLBElement::returnNode()
{
    bNode = new BNode;
    b = new RenderNode;
    b = bNode;

    return b;
}

void HTMLBElement::deleteHTMLElement()
{
    delete bNode;
    delete b;
}
