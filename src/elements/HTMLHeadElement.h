#ifndef HEADELEMENT_H
#define HEADELEMENT_H

#include "HTMLElement.h"
#include "nodes/headnode.h"

class HTMLHeadElement : public HTMLElement
{
public:
    HTMLHeadElement();
    virtual HeadNode *returnNode();
    virtual void deleteHTMLElement();

private:
    HeadNode *headNode;

};

#endif // HEADELEMENT_H
