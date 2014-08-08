#ifndef TEXTPAINTNODE_H
#define TEXTPAINTNODE_H

#include "paintnode.h"

class TextPaintNode : public PaintNode
{
public:
    TextPaintNode(std::string textToSet);
    virtual void paint(WWPainter *wwPainter, PaintArea *display, Layout *layout);
    virtual void calculateDimensions(PaintArea *display);

private:
    std::string text;
    QFont createFontForNode(WWPainter *wwPainter);
};

#endif // TEXTPAINTNODE_H
