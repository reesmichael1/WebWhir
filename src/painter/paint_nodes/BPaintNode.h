#ifndef BPAINTNODE_H
#define BPAINTNODE_H

#include "../paintarea.h"
#include "ParagraphPaintNode.h"

class BPaintNode : public ParagraphPaintNode
{
public:
    BPaintNode();

private:
    std::string text;
};

#endif // BPAINTNODE_H
