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
    virtual void paint(WWPainter *wwPainter, PaintArea *display, Layout *layout);
    void paintChildNodes(WWPainter *wwPainter, PaintArea *display, Layout *layout);
    virtual void calculateDimensions(PaintArea *display);
    std::vector<PaintNode*> getChildPaintNodes();
    QSize getDimensions();
    QPoint getCoordinates();
    void setCoordinates(QPoint coordinatesToSet);
    int getWidth();
    int getHeight();
    enum paintOption {
        boldText,
    };
    void addPaintOption(paintOption optionToAdd);
    std::vector<int> getPaintOptions();
    void setIsInline(bool inlineOrNot);
    bool isInlineNode();

protected:
    QSize dimensions;
    QPoint coordinates;
    std::vector<PaintNode*> childPaintNodes;
    std::vector<int> paintOptions;

private:
    bool inlineNode;
    bool needsPainting;
};

#endif // PAINTNODE_H
