#ifndef IMAGENODE_H
#define IMAGENODE_H

#include <string>

#include "imagenode.h"
#include "rendernode.h"

class ImageNode : public RenderNode
{
public:
    ImageNode();
    virtual std::string getSoucePath();
    void setSourcePath(std::string path);
    virtual std::string getAltText();
    void setAltText(std::string text);

private:
    std::string sourcePath;
    std::string altText;
};

#endif // IMAGENODE_H
