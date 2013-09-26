#ifndef HTMLLIELEMENT_H
#define HTMLLIELEMENT_H

#include "HTMLElement.h"
#include "nodes/listnode.h"

class HTMLLiElement : public HTMLElement
{
public:
    HTMLLiElement();
    virtual ListNode *returnNode();

private:
    ListNode *listNode;
};

#endif // HTMLLIELEMENT_H
