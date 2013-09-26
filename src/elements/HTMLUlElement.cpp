#include "HTMLUlElement.h"

HTMLUlElement::HTMLUlElement()
{
}

UlNode* HTMLUlElement::returnNode()
{
    ulNode = new UlNode;

    return ulNode;
}
