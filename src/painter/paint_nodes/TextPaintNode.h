#ifndef TEXTPAINTNODE_H
#define TEXTPAINTNODE_H

#include "paintnode.h"

class TextPaintNode : public PaintNode
{
public:
    TextPaintNode(std::string textToSet);
    ~TextPaintNode();
    virtual void paint(WWPainter &wwPainter, PaintArea *display, Layout *layout);
    virtual void calculateDimensions(PaintArea *display);
    virtual QSize getDimensions(PaintArea *display);

private:
    QHash<QString, int> characterHash;
    QStringList lineList;
    std::string text;
    QFont createFontForNode(WWPainter &wwPainter);
    QFont createFontForNode();
    void splitTextIntoLinesForDisplay(PaintArea *display, WWPainter &wwPainter);
    void drawLines(WWPainter *wwPainter, PaintArea *display);
    QFontMetrics *fm;
};

#endif // TEXTPAINTNODE_H
