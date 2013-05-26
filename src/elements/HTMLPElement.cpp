#include "HTMLPElement.h"
#include "nodes/rendernode.h"
#include "nodes/textnode.h"

HTMLPElement::HTMLPElement()
{
}

RenderNode* HTMLPElement::returnNode()
{
    textNode = new TextNode;
    text = new RenderNode;
    text = textNode;

    return text;
}

void HTMLPElement::deleteHTMLElement()
{
    delete textNode;
    delete text;
}

