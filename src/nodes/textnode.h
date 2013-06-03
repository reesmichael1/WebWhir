#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "rendernode.h"

class TextNode : public RenderNode
{
public:
    TextNode();
    virtual void setText(std::string textToSet);
    std::string getText();
    void setTextCharacterSize(int size);
    int getTextCharacterSize();
    virtual void paintNode();

private:
    std::string text;
    int textCharacterSize;

};

#endif // TEXTNODE_H
