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
    PaintNode(RenderNode *nodeToAdd);
    ~PaintNode();
    void setWeight(QFont::Weight weight = QFont::Normal);
    void setStyle(QFont::Style style = QFont::StyleNormal);
    QFont::Weight getWeight();
    QFont::Style getStyle();
    char *getCharacter();
    std::string getSourcePath();
    std::string getAltText();
    RenderNode *returnNode();
    std::string getTypeOfPaintNode();

private:
    QFont::Weight characterWeight;
    QFont::Style characterStyle;
    std::string *typeOfNode;
    char *character;
    RenderNode *node;
    std::string *sourcePath;
    std::string *altText;
};

#endif // PAINTNODE_H
