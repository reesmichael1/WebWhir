#include "paintnode.h"

PaintNode::PaintNode(const char c)
{
    character = new char;
    typeOfNode = new std::string;
    *character = c;
    node = NULL;
    sourcePath = NULL;
    altText = NULL;

    characterWeight = QFont::Normal;

    *typeOfNode = "char";
}

PaintNode::PaintNode(RenderNode *nodeToAdd)
{
    typeOfNode = new std::string;

    if (nodeToAdd->getTypeOfRenderNode() == "image")
    {
        character = NULL;
        node = NULL;
        sourcePath = new std::string;
        altText = new std::string;

        sourcePath = nodeToAdd->getSourcePath();
        altText = nodeToAdd->getAltText();
        *typeOfNode = "image";
    }

    else if (nodeToAdd->getTypeOfRenderNode() == "hr")
    {
        character = NULL;
        node = NULL;
        sourcePath = NULL;
        altText = NULL;

        *typeOfNode = "hr";
    }

    else if (nodeToAdd->getTypeOfRenderNode() == "ul")
    {
        character = NULL;
        sourcePath = NULL;
        altText = NULL;

        node = new RenderNode;
        node = nodeToAdd;

        *typeOfNode = "ul";
    }

    else if (nodeToAdd->getTypeOfRenderNode() == "li")
    {
        character = NULL;
        sourcePath = NULL;
        altText = NULL;

        node = new RenderNode;
        node = nodeToAdd;

        *typeOfNode = "li";
    }

    else
    {
        node = new RenderNode;
        node = nodeToAdd;

        character = NULL;
        sourcePath = NULL;
        altText = NULL;

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

std::string PaintNode::getAltText()
{
    return *altText;
}

std::string PaintNode::getSourcePath()
{
    return *sourcePath;
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

void PaintNode::setStyle(QFont::Style style)
{
    characterStyle = style;
}

QFont::Weight PaintNode::getWeight()
{
    return characterWeight;
}

QFont::Style PaintNode::getStyle()
{
    return characterStyle;
}
