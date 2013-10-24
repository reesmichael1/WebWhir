#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

#include "document.h"
#include "paintnode.h"

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    PaintArea(QWidget *parent);
    void constructPaintNodeTree(std::vector<RenderNode *> renderNodeTree);
    void setDocument(Document *documentToSet);
    PaintNode* renderNodeToPaintNode(RenderNode *renderNode);
    void paintDocument(QPainter *qPainter);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Document *webpage;
    std::vector<PaintNode*> *paintNodeTree;
    bool paintingComplete;
};

#endif // PAINTAREA_H
