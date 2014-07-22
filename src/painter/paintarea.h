#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

#include "document.h"
#include "paint_nodes/paintnode.h"

class RenderNode;
class Document;
class PaintNode;
class Layout;

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    PaintArea(QWidget *parent);
    ~PaintArea();
    void constructPaintNodeTree(std::vector<RenderNode*> renderNodeTree);
    void setDocument(Document *documentToSet);
    PaintNode* renderNodeToPaintNode(RenderNode *renderNode);
    void paintDocument(QPainter *qPainter);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Document *webpage;
    std::vector<PaintNode*> *paintNodeTree;
    bool paintingComplete;
    QRect getBoundingRectangle(PaintNode *paintNode);
    void resetPaintArea();
    void emptyPaintNodeTree();
    Layout* layout;
};

#endif // PAINTAREA_H
