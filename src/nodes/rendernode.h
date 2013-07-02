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
    virtual void paintNode();
    virtual void addCharacter(std::string::iterator i);
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


    //This strikes me as a really bad idea. I'm doing it now, hopefully temporarily,
    //to see how it works out.
    std::string typeOfNode;

};

#endif // RENDERNODE_H
