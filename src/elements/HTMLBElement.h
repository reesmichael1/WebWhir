#ifndef HTMLBELEMENT_H
#define HTMLBELEMENT_H

#include "HTMLElement.h"
#include "nodes/bnode.h"

class HTMLBElement : HTMLElement
{
public:
    HTMLBElement();
    virtual BNode *returnNode();
    virtual void deleteHTMLElement();

private:
    BNode *bNode;
};

#endif // HTMLBELEMENT_H
