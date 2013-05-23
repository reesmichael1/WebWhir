#include "HTMLPElement.h"
#include "nodes/rendernode.h"
#include "nodes/textnode.h"

HTMLPElement::HTMLPElement()
{
}

RenderNode* HTMLPElement::returnNode()
{
    TextNode textNode;
    RenderNode *text = &textNode;
    return text;
}

