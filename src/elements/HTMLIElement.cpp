#include "HTMLIElement.h"

HTMLIElement::HTMLIElement()
{
}

INode* HTMLIElement::returnNode()
{
    iNode = new INode;

    return iNode;
}
