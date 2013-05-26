#include "HTMLPElement.h"
#include "nodes/rendernode.h"
#include "nodes/textnode.h"

HTMLPElement::HTMLPElement()
{
}

RenderNode* HTMLPElement::returnNode()
{
    TextNode *textNode = new TextNode;
    RenderNode *text = new RenderNode;
    text = textNode;
    text->setChildNode(NULL);
    return text;
}

