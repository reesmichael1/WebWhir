#ifndef LAYOUT_H
#define LAYOUT_H

#include "painter/paint_nodes/paintnode.h"

class PaintNode;

class Layout
{
public:
    Layout();
    void addPaintNode(PaintNode *nodeToAdd);
    int getHeight();

private:
    QPoint origin;
    QSize size;
    std::vector<PaintNode*> paintNodes;
};

#endif // LAYOUT_H
