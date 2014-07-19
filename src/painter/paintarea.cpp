#include <QPainter>
#include <QLabel>
#include <QString>

#include "paintarea.h"
#include "layout/layout.h"

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
        paintNodeTree->push_back((*i)->convertToPaintNode());
    }
}

void PaintArea::paintDocument(QPainter *qPainter)
{
    Layout *layout = new Layout;

    for (std::vector<PaintNode*>::iterator i = paintNodeTree->begin();
         i != paintNodeTree->end(); i++)
    {
        (*i)->paint(qPainter, this, layout);
    }

    this->setMinimumHeight(layout->getHeight());
    paintingComplete = true;
}

QRect PaintArea::getBoundingRectangle(PaintNode *paintNode)
{
    return QRect(0, 0, 100, 100);
}
