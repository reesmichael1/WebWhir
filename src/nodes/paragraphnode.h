#ifndef PARAGRAPHNODE_H
#define PARAGRAPHNODE_H

#include "rendernode.h"

class ParagraphNode : public RenderNode
{
public:
    ParagraphNode();
    virtual PaintNode* convertToPaintNode();
    virtual void addText(std::string textToSet);
    virtual std::string getText();
};

#endif // TEXTNODE_H
