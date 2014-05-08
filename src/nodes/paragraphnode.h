#ifndef PARAGRAPHNODE_H
#define PARAGRAPHNODE_H

#include "rendernode.h"

class ParagraphNode : public RenderNode
{
public:
    ParagraphNode();
    virtual PaintNode* convertToPaintNode();

};

#endif // TEXTNODE_H
