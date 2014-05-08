#ifndef PAINTNODE_H
#define PAINTNODE_H

#include <QSize>

#include <string>

#include "nodes/rendernode.h"
#include "../paintarea.h"

class RenderNode;
class PaintArea;

class PaintNode {
public:
    PaintNode();
    void addChildPaintNodes(std::vector<PaintNode*>
                            childNodes);
    virtual void paint(QPainter *qPainter, PaintArea *display);
    void paintChildNodes(QPainter *qPainter, PaintArea *display);
    virtual QSize getDimensions();

private:
    bool needsPainting;
    std::vector<PaintNode*> childPaintNodes;
};

#endif // PAINTNODE_H
