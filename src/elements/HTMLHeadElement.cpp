#include "HTMLHeadElement.h"
#include "nodes/rendernode.h"
#include "nodes/headnode.h"

HTMLHeadElement::HTMLHeadElement()
{
}

RenderNode* HTMLHeadElement::returnNode()
{
    HeadNode headNode;
    RenderNode *head = &headNode;
    return head;
}

