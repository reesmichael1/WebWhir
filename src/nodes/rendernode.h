#ifndef RENDERNODE_H
#define RENDERNODE_H

class RenderNode
{
public:
    RenderNode();
    virtual void paintNode();
    void setNeedsPainting(bool valueToSet);
    RenderNode* getChildNode();
    void setChildNode(RenderNode *nodeToAdd);

private:
    RenderNode *childNodePointer;
    bool needsPainting;
};

#endif // RENDERNODE_H
