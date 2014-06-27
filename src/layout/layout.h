#ifndef LAYOUT_H
#define LAYOUT_H

#include "painter/paint_nodes/paintnode.h"

class PaintNode;

/*!
    \class Layout
    \brief The Layout class determines what coordinates should be 
    assigned to paint nodes as they are added to the render tree.

    \since 0.2

    \ingroup painting

    Layout assigns coordinates to PaintNodes. When a paint node is passed
    through \l{addPaintNode}, it is assigned an origin and a size. The origin
    is a QPoint that specifies where the upper-left corner of the node should
    be painted, and size is a QSize that specifies how large the node will be
    when painted into the current window.

    The size represents the complete size of the node when painted. This means
    that the sizes of any child nodes must also be computed during the process
    of painting.
*/

class Layout
{
public:
    Layout();
    void addPaintNode(PaintNode *nodeToAdd);
    int getHeight();
    void reset();

private:
    QPoint origin;
    QSize size;
    std::vector<PaintNode*> paintNodes;
};

#endif // LAYOUT_H
