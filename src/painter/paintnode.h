#ifndef PAINTNODE_H
#define PAINTNODE_H

#include <string>

#include "nodes/rendernode.h"

#include <QFont>

class RenderNode;

class PaintNode
{
public:
    PaintNode(const char c);
    PaintNode(RenderNode *nodeToAdd, std::string nodeType);
    PaintNode(RenderNode *nodeToAdd);
    ~PaintNode();
    void setWeight(QFont::Weight weight = QFont::Normal);
    QFont::Weight getWeight();
    char *getCharacter();
    RenderNode *returnNode();
    std::string getTypeOfPaintNode();

private:
    QFont::Weight characterWeight;
    std::string *typeOfNode;
    char *character;
    RenderNode *node;
    std::string sourcePath;
};

#endif // PAINTNODE_H
