#include "HTMLHrElement.h"

HTMLHrElement::HTMLHrElement()
{
}

HorizontalRuleNode* HTMLHrElement::returnNode()
{
    hrNode = new HorizontalRuleNode;

    return hrNode;
}
