#ifndef HTMLPELEMENT_H
#define HTMLPELEMENT_H

#include "HTMLElement.h"
#include "nodes/textnode.h"

class HTMLPElement : HTMLElement
{
public:
    HTMLPElement();
    virtual RenderNode *returnNode();
    virtual void deleteHTMLElement();

private:
    TextNode *textNode;
    RenderNode *text;
};

#endif // HTMLPELEMENT_H
