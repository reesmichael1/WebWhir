#ifndef TEXTPAINTNODE_H
#define TEXTPAINTNODE_H

#include "paintnode.h"

class TextPaintNode : public PaintNode
{
public:
    TextPaintNode(std::string textToSet);
    virtual void paint(WWPainter *wwPainter, PaintArea *display, Layout *layout);
    virtual void calculateDimensions(PaintArea *display);
    int getXCoordinateOfEdgeOfLastLine();

private:
    int xCoordinateOfEdgeOfLastLine;
    int xCoordinateOfStartOfFirstLine;
    QStringList lineList;
    std::string text;
    QFont createFontForNode(WWPainter *wwPainter);
    void splitTextIntoLinesForDisplay(PaintArea *display, WWPainter *wwPainter);
    void drawLines(WWPainter *wwPainter);
};

#endif // TEXTPAINTNODE_H
