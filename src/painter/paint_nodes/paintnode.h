#ifndef PAINTNODE_H
#define PAINTNODE_H

#include <QSize>

#include <string>

#include "nodes/rendernode.h"
#include "../paintarea.h"
#include "layout/layout.h"
#include "painter/wwPainter/wwpainter.h"

class RenderNode;
class PaintArea;
class Layout;

class PaintNode {
public:
    PaintNode();
    ~PaintNode();
    void emptyChildPaintNodes();
    void addChildPaintNodes(std::vector<PaintNode*>
                            childNodes);
    virtual void paint(WWPainter &wwPainter, PaintArea *display, Layout *layout);
    void paintChildNodes(WWPainter &wwPainter, PaintArea *display, Layout *layout);
    virtual void calculateDimensions(PaintArea *display);
    std::vector<PaintNode*> getChildPaintNodes();
    virtual QSize getDimensions(PaintArea *display);
    QPoint getCoordinates();
    void setCoordinates(QPoint coordinatesToSet);
    int getWidth();
    int getHeight();
    enum paintOption {
        boldText,
    };
    void addPaintOption(paintOption optionToAdd);
    std::vector<int> getPaintOptions();
    int getXCoordinateOfEdgeOfLastLine();
    void setXCoordinateOfStartOfFirstLine(int xToSet);
    void setNeedsPainting(bool valueToSet);
    bool getNeedsPainting();
    virtual bool regionContainsPaintNode(const QRegion &region);
    bool getIsInline();
    void setIsInline(bool inlineOrNot);
    void resetPaintNode();

protected:
    QSize dimensions;
    QPoint coordinates;
    std::vector<PaintNode*> childPaintNodes;
    std::vector<int> paintOptions;
    int xCoordinateOfEdgeOfLastLine;
    int xCoordinateOfStartOfFirstLine;
    bool isInline;

private:
    bool needsPainting;
};

#endif // PAINTNODE_H
