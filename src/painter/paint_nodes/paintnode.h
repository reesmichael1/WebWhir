#ifndef PAINTNODE_H
#define PAINTNODE_H

#include <QSize>

#include <string>

#include "nodes/rendernode.h"
#include "../paintarea.h"
#include "layout/layout.h"

class RenderNode;
class PaintArea;
class Layout;

class PaintNode {
public:
    PaintNode();
    void addChildPaintNodes(std::vector<PaintNode*>
                            childNodes);
    virtual void paint(QPainter *qPainter, PaintArea *display, Layout *layout);
    void paintChildNodes(QPainter *qPainter, PaintArea *display, Layout *layout);
    virtual void calculateDimensions(PaintArea *display);
    QSize getDimensions();
    QPoint getCoordinates();
    void setCoordinates(QPoint coordinatesToSet);
    int getWidth();
    int getHeight();

protected:
    QSize dimensions;
    QPoint coordinates;

private:
    bool needsPainting;
    std::vector<PaintNode*> childPaintNodes;
};

#endif // PAINTNODE_H
