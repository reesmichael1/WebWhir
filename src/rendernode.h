#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <string>

class RenderNode
{
public:
    RenderNode();
    virtual std::string getText();
    RenderNode *childNode;

private:
    bool needsPainting;
};

#endif // RENDERNODE_H
