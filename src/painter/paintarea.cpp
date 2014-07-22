#include <QPainter>
#include <QLabel>
#include <QString>

#include "paintarea.h"
#include "layout/layout.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    paintNodeTree = new std::vector<PaintNode*>;

    layout = new Layout;
    paintingComplete = false;
}

PaintArea::~PaintArea()
{
    delete layout;
    emptyPaintNodeTree();
    delete paintNodeTree;
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
    emptyPaintNodeTree();
    std::vector<RenderNode*>::iterator i = renderNodeTree.begin();

    for (; i != renderNodeTree.end(); i++)
    {
        paintNodeTree->push_back((*i)->convertToPaintNode());
    }
}

void PaintArea::paintDocument(QPainter *qPainter)
{
    resetPaintArea();
    for (PaintNode* paintNode : *paintNodeTree)
    {
        paintNode->paint(qPainter, this, layout);
    }

    this->setMinimumHeight(layout->getHeight());
    paintingComplete = true;
}

QRect PaintArea::getBoundingRectangle(PaintNode *paintNode)
{
    return QRect(0, 0, 100, 100);
}

void PaintArea::resetPaintArea()
{
    QPainter qPainter(this);
    qPainter.eraseRect(QRect(layout->getOrigin(), layout->getSize()));
    layout->reset();
}

void PaintArea::emptyPaintNodeTree()
{
    while (!paintNodeTree->empty())
    {
        delete paintNodeTree->back();
        paintNodeTree->pop_back();
    }
}
