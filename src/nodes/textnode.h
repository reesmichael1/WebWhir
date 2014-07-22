#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "rendernode.h"

class TextNode : public RenderNode
{
public:
    TextNode(std::string textToSet);
    virtual PaintNode* convertToPaintNode();
    virtual std::string getText();

private:
    std::string text;
};

#endif // TEXTNODE_H
