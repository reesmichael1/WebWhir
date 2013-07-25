#ifndef PAINTNODE_H
#define PAINTNODE_H

#include <string>

class RenderNode;

class PaintNode
{
public:
    PaintNode(const char c);
    PaintNode(RenderNode *nodeToAdd);
    ~PaintNode();
    void setWeight(QFont::Weight weight = QFont::Normal);
    QFont::Weight getWeight();
    char *returnCharacter();
    RenderNode *returnNode();
    std::string getTypeOfPaintNode();

private:
    QFont::Weight characterWeight;
    std::string typeOfNode;
    char *character;
    RenderNode *node;
};

#endif // PAINTNODE_H
