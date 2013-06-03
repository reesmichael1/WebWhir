#ifndef HTMLBELEMENT_H
#define HTMLBELEMENT_H

#include "HTMLElement.h"
#include "nodes/bnode.h"

class HTMLBElement : HTMLElement
{
public:
    HTMLBElement();
    virtual RenderNode *returnNode();
    virtual void deleteHTMLElement();

private:
    BNode *bNode;
    RenderNode *b;
};

#endif // HTMLBELEMENT_H
