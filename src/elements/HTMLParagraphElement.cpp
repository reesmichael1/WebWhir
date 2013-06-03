#include "HTMLParagraphElement.h"
#include "nodes/rendernode.h"
#include "nodes/paragraphnode.h"

HTMLParagraphElement::HTMLParagraphElement()
{
}

RenderNode* HTMLParagraphElement::returnNode()
{
    paragraphNode = new ParagraphNode;
    paragraph = new RenderNode;
    paragraph = paragraphNode;

    return paragraph;
}

void HTMLParagraphElement::deleteHTMLElement()
{
    delete paragraphNode;
    delete paragraph;
}

