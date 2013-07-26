#include "HTMLParagraphElement.h"
#include "nodes/rendernode.h"
#include "nodes/paragraphnode.h"

HTMLParagraphElement::HTMLParagraphElement()
{
}

ParagraphNode* HTMLParagraphElement::returnNode()
{
    paragraphNode = new ParagraphNode;

    return paragraphNode;
}
