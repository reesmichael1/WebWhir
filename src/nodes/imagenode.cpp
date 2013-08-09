#include "imagenode.h"

ImageNode::ImageNode()
{
    setNeedsPainting(true);
    setTypeOfRenderNode("image");
}

std::string ImageNode::getSoucePath()
{
    return sourcePath;
}

void ImageNode::setSourcePath(std::string path)
{
    sourcePath = path;
}

std::string ImageNode::getAltText()
{
    return altText;
}

void ImageNode::setAltText(std::string text)
{
    altText = text;
}
