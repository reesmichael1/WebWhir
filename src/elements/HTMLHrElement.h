#ifndef HTMLHRELEMENT_H
#define HTMLHRELEMENT_H

#include "HTMLElement.h"
#include "nodes/horizontalrulenode.h"

class HTMLHrElement : public HTMLElement
{
public:
    HTMLHrElement();
    virtual HorizontalRuleNode* returnNode();

private:
    HorizontalRuleNode *hrNode;
};

#endif // HTMLHRELEMENT_H
