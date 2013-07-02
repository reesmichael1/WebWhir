#ifndef PAINTNODE_H
#define PAINTNODE_H

#include "painter/painter.h"

class RenderNode;

class PaintNode
{
public:
    PaintNode(const char c, Painter *painterToAdd);
    PaintNode(RenderNode *nodeToAdd, Painter *painterToAdd);
    ~PaintNode();
    void paint(QFont::Weight weight = QFont::Normal);

private:
    char *character;
    RenderNode *node;
    Painter *painter;
};

#endif // PAINTNODE_H
