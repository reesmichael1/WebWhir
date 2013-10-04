#ifndef HTMLIELEMENT_H
#define HTMLIELEMENT_H

#include "HTMLElement.h"
#include "nodes/inode.h"

class HTMLIElement : public HTMLElement
{
public:
    HTMLIElement();
    virtual INode* returnNode();

private:
    INode *iNode;
};

#endif // HTMLIELEMENT_H
