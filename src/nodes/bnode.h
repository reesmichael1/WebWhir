#ifndef BNODE_H
#define BNODE_H

#include <string>
#include "nodes/paragraphnode.h"

class BNode : public RenderNode
{
public:
    BNode();
    std::string getText();
    virtual void setText(std::string textToSet);

private:
    std::string text;
};

#endif // BNODE_H
