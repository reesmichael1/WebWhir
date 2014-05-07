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
    void setPaintArea(PaintArea *paintArea);
    void paint();

private:
    bool bold;
    bool needsPainting;
    std::vector<PaintNode*> childPaintNodes;
    QSize getDimensions();
    PaintArea *display;
};

#endif // PAINTNODE_H
