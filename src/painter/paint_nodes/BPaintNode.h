#ifndef BPAINTNODE_H
#define BPAINTNODE_H

#include "../paintarea.h"
#include "ParagraphPaintNode.h"

class BPaintNode : public ParagraphPaintNode
{
public:
    BPaintNode();
    virtual void paint(QPainter *qPainter, PaintArea *display, Layout *layout);
};

#endif // BPAINTNODE_H
