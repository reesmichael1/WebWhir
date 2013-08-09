#ifndef HTMLIMGELEMENT_H
#define HTMLIMGELEMENT_H

#include <string>

#include "HTMLElement.h"
#include "nodes/imagenode.h"

class HTMLImgElement : public HTMLElement
{
public:
    HTMLImgElement();
    void setSourcePath(std::string path);
    void setAltText(std::string text);
    virtual ImageNode* returnNode();

private:
    std::string sourcePath;
    std::string altText;
    ImageNode *node;
};

#endif // HTMLIMGELEMENT_H
