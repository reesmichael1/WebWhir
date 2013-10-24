#include <QPainter>
#include <QString>

#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    paintNodeTree = new std::vector<PaintNode*>;

    paintingComplete = false;
}

void PaintArea::setDocument(Document *documentToSet)
{
    webpage = documentToSet;
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (!paintNodeTree->empty())
    {
        QPainter qPainter(this);
        paintDocument(&qPainter);
    }
}

void PaintArea::constructPaintNodeTree(std::vector<RenderNode*>
                                       renderNodeTree)
{
    std::vector<RenderNode*>::iterator i = renderNodeTree.begin();

    for (; i != renderNodeTree.end(); i++)
    {
        paintNodeTree->push_back(renderNodeToPaintNode(*i));
    }
}

PaintNode* PaintArea::renderNodeToPaintNode(RenderNode *renderNode)
{
    PaintNode *paintNode = new PaintNode(renderNode);

    std::vector<RenderNode*> *childNodes = renderNode->getChildNodes();

    if (!childNodes->empty())
    {
        std::vector<RenderNode*>::iterator i = childNodes->begin();
        std::vector<PaintNode*> childPaintNodes;

        for (; i != childNodes->end(); i++)
        {
            childPaintNodes.push_back(renderNodeToPaintNode(*i));
        }

        paintNode->addChildPaintNodes(childPaintNodes);

    }

    return paintNode;
}

void PaintArea::paintDocument(QPainter *qPainter)
{
    QString test = "Hello world! I'm just going to type a lot of words here to show how text wrapping works when implemented using Qt's library. It's much more efficient than my hard-coded algorithm!";
    QRect *boundingRect = new QRect(0, 0, 0, 0);
    qPainter->drawText(this->geometry(), Qt::TextWordWrap, test, boundingRect);
    setMinimumHeight(boundingRect->height());
    delete boundingRect;
}
