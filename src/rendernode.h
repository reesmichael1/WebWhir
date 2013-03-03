#ifndef RENDERNODE_H
#define RENDERNODE_H

#include <string>

class RenderNode
{
public:
    RenderNode();
    void appendText(std::string *textToSet);
    std::string getText();

private:
    std::string text;
};

#endif // RENDERNODE_H
