#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "rendernode.h"

class ParagraphNode : public RenderNode
{
public:
    ParagraphNode();
    virtual void addCharacter(std::string::iterator i);
    std::string getText();
    void setTextCharacterSize(int size);
    int getTextCharacterSize();
    virtual void paintNode(std::string *webpageString);

private:
    std::string text;
    int textCharacterSize;

};

#endif // TEXTNODE_H
