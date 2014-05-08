#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <iostream>
#include <string>
#include <vector>

#include "painter/paint_nodes/paintnode.h"

class PaintNode;

class RenderNode
{
public:
    RenderNode();
    RenderNode(std::string nodeText);
    virtual ~RenderNode();
    virtual std::string* getSourcePath();
    virtual std::string* getAltText();
    void setNeedsPainting(bool valueToSet);
    void setTypeOfRenderNode(std::string typeToSet);
    std::string getTypeOfRenderNode();
    void setParentNode(RenderNode *nodeToSet);
    RenderNode* getParentNode();
    void addChildNode(RenderNode *nodeToAdd);
    void deleteChildNodes();
    std::vector<RenderNode*> *getChildNodes();
    void setText(std::string textToSet);
    std::string getText();
    void setIsOpen(bool valueToSet);
    bool getIsOpen();
    virtual PaintNode* convertToPaintNode();
    std::vector<PaintNode*> convertChildNodesToPaintNodes();

protected:
    RenderNode *parentNode;
    bool isOpen;
    bool needsPainting;
    std::vector<RenderNode*> *childNodes;
    std::string *typeOfNode;
    std::string text;
};

#endif // RENDERNODE_H
