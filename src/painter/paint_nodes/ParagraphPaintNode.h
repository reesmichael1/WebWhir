#ifndef PARAGRAPHPAINTNODE_H
#define PARAGRAPHPAINTNODE_H

#include "paintnode.h"

class ParagraphPaintNode : public PaintNode
{
public:
    ParagraphPaintNode();
    std::string getText();
    void setText(std::string textToSet);

private:
    std::string text;
};

#endif // PARAGRAPHPAINTNODE_H
