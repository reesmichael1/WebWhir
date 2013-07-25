#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <iostream>
#include <string>
#include <vector>

#include "painter/paintnode.h"

class PaintNode;

class RenderNode
{
public:
    RenderNode();
    virtual ~RenderNode();
    void setNeedsPainting(bool valueToSet);
    void setTypeOfNode(std::string typeToSet);
    std::string getTypeOfNode();
    void setParentNode(RenderNode *nodeToSet);
    RenderNode* getParentNode();
    void addChildNode(RenderNode *nodeToAdd);
    void addPaintNode(PaintNode *nodeToAdd);
    std::vector<RenderNode *> *getChildNodes();
    std::vector<PaintNode *> *getPaintNodes();
    void setIsOpen(bool valueToSet);
    bool getIsOpen();

protected:
    RenderNode *parentNode;
    bool isOpen;
    bool needsPainting;
    std::vector<RenderNode*> *childNodes;
    std::vector<PaintNode*> *paintNodes;
    std::string typeOfNode;

};

#endif // RENDERNODE_H
