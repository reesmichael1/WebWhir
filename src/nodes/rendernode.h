#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <iostream>
#include <vector>

class RenderNode
{
public:
    RenderNode();
    virtual void paintNode();
    void setNeedsPainting(bool valueToSet);
    void setTypeOfNode(std::string typeToSet);
    std::string getTypeOfNode();
    void setParentNode(RenderNode *nodeToSet);
    void addChildNode(RenderNode *nodeToAdd);
    void setIsOpen(bool valueToSet);
    bool getIsOpen();

private:
    RenderNode *parentNode;
    bool isOpen;
    bool needsPainting;
    std::vector<RenderNode*> childNodes;


    //This strikes me as a really bad idea. I'm doing it now, hopefully temporarily,
    //to see how it works out.
    std::string typeOfNode;

};

#endif // RENDERNODE_H
