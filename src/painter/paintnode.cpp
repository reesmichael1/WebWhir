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
    if (nodeToAdd->getTypeOfRenderNode() == "img")
    {
        sourcePath = nodeToAdd->getSourcePath();
        *typeOfNode = "image";
    }

    else
    {
        node = new RenderNode;
        typeOfNode = new std::string;
        node = nodeToAdd;

        character = NULL;

        *typeOfNode = "node";
    }
}

PaintNode::~PaintNode()
{
    //node is freed during the destruction of the webpage, which
    //deletes all of the render nodes created during tokenization.
    delete character;
    delete typeOfNode;
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

void PaintNode::setWeight(QFont::Weight weight)
{
    characterWeight = weight;
}

QFont::Weight PaintNode::getWeight()
{
    return characterWeight;
}
