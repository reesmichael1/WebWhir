#include "paintnode.h"

PaintNode::PaintNode(const char c)
{
    character = new char;
    typeOfNode = new std::string;
    *character = c;
    node = NULL;

    characterWeight = QFont::Normal;

    *typeOfNode = "char";
}

PaintNode::PaintNode(RenderNode *nodeToAdd)
{
    node = new RenderNode;
    typeOfNode = new std::string;
    node = nodeToAdd;

    character = NULL;

    *typeOfNode = "node";
}

char *PaintNode::getCharacter()
{
    return character;
}

RenderNode* PaintNode::returnNode()
{
    return node;
}

std::string PaintNode::getTypeOfPaintNode()
{
    return *typeOfNode;
}

PaintNode::~PaintNode()
{
    delete character;
}

void PaintNode::setWeight(QFont::Weight weight)
{
    characterWeight = weight;
}

QFont::Weight PaintNode::getWeight()
{
    return characterWeight;
}
