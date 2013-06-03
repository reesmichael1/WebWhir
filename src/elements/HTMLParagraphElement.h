#ifndef HTMLPELEMENT_H
#define HTMLPELEMENT_H

#include "HTMLElement.h"
#include "nodes/paragraphnode.h"

class HTMLParagraphElement : HTMLElement
{
public:
    HTMLParagraphElement();
    virtual RenderNode *returnNode();
    virtual void deleteHTMLElement();

private:
    ParagraphNode *paragraphNode;
    RenderNode *paragraph;
};

#endif // HTMLPELEMENT_H
