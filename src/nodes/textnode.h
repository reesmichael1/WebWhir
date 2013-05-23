#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "rendernode.h"

class TextNode : public RenderNode
{
public:
    TextNode();
    void setText(std::string textToSet);
    void setTextCharacterSize(int size);
    int getTextCharacterSize();
    virtual std::string getText();

private:
    std::string text;
    int textCharacterSize;

};

#endif // TEXTNODE_H
