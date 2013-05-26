#include "HTMLHeadElement.h"
#include "nodes/rendernode.h"
#include "nodes/headnode.h"

HTMLHeadElement::HTMLHeadElement()
{
}

RenderNode* HTMLHeadElement::returnNode()
{
    headNode = new HeadNode;
    head = new RenderNode;
    head = headNode;

    return head;
}

void HTMLHeadElement::deleteHTMLElement()
{
    delete headNode;
    delete head;
}
