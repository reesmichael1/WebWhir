#include "paintnode.h"

PaintNode::PaintNode(const char c)
{
    character = new char;
    *character = c;
    node = NULL;

    characterWeight = QFont::Normal;

    typeOfNode = "char";
}

PaintNode::PaintNode(RenderNode *nodeToAdd)
{
    node = new RenderNode;
    node = nodeToAdd;

    character = NULL;

    typeOfNode = "node";
}

char *PaintNode::returnCharacter()
{
    return character;
}

RenderNode* PaintNode::returnNode()
{
    return node;
}

std::string PaintNode::getTypeOfNode()
{
    return typeOfNode;
}

PaintNode::~PaintNode()
{
    delete character;
    delete node;
}

void PaintNode::setWeight(QFont::Weight weight)
{
    characterWeight = weight;
}

QFont::Weight PaintNode::getWeight()
{
    return characterWeight;
}
