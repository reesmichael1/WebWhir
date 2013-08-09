#include "HTMLImgElement.h"

HTMLImgElement::HTMLImgElement()
{
}

void HTMLImgElement::setSourcePath(std::string path)
{
    sourcePath = path;
}

void HTMLImgElement::setAltText(std::string text)
{
    altText = text;
}

ImageNode *HTMLImgElement::returnNode()
{
    node = new ImageNode;
    node->setAltText(altText);
    node->setSourcePath(sourcePath);
    return node;
}
