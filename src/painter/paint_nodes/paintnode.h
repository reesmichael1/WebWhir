#ifndef PAINTNODE_H
#define PAINTNODE_H

#include <QSize>

#include <string>

#include "nodes/rendernode.h"

class RenderNode;

class PaintNode {
public:
    PaintNode();
    PaintNode(RenderNode *node);
    void addChildPaintNodes(std::vector<PaintNode*>
                            childNodes);

private:
    bool bold;
    //Should I call this dirty or needsPainting?
    bool dirty;
    std::string text;
    std::vector<PaintNode*> childPaintNodes;
    QSize getDimensions();
};

#endif // PAINTNODE_H
