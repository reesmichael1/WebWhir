#include "HTMLHeadElement.h"
#include "nodes/rendernode.h"
#include "nodes/headnode.h"

HTMLHeadElement::HTMLHeadElement()
{
}

HeadNode* HTMLHeadElement::returnNode()
{
    headNode = new HeadNode;

    return headNode;
}

void HTMLHeadElement::deleteHTMLElement()
{
    delete headNode;
}
