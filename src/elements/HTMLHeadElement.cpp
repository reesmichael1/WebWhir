#include "HTMLHeadElement.h"
#include "nodes/rendernode.h"
#include "nodes/headnode.h"

HTMLHeadElement::HTMLHeadElement()
{
}

RenderNode* HTMLHeadElement::returnNode()
{
    HeadNode *headNode = new HeadNode;
    RenderNode *head = new RenderNode;
    head = headNode;
    head->setChildNode(NULL);
    return head;
}

