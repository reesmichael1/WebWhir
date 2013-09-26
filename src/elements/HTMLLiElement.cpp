#include "HTMLLiElement.h"

HTMLLiElement::HTMLLiElement()
{
}

ListNode* HTMLLiElement::returnNode()
{
    listNode = new ListNode;

    return listNode;
}
