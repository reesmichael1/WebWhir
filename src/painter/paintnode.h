#ifndef PAINTNODE_H
#define PAINTNODE_H

#include <string>

#include "nodes/rendernode.h"

class RenderNode;

class PaintNode {
public:
    PaintNode(RenderNode *node);
    void addChildPaintNodes(std::vector<PaintNode*>
                            childNodes);

private:
    bool bold;
    std::string text;
    std::vector<PaintNode*> childPaintNodes;
};

#endif // PAINTNODE_H
