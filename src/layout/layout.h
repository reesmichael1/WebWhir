#ifndef LAYOUT_H
#define LAYOUT_H

#include "painter/paint_nodes/paintnode.h"
#include "painter/paintarea.h"

class PaintNode;
class PaintArea;

class Layout
{
public:
    Layout();
    void addPaintNode(PaintNode *nodeToAdd, PaintArea *display);
    int getHeight();
    void reset();
    QPoint getOrigin();
    QSize getSize();

private:
    QPoint origin;
    QSize size;
    int lastX;
    std::vector<PaintNode*> paintNodes;
    int calculateNewXAfterAddingNode(PaintNode *newNode);
};

#endif // LAYOUT_H
