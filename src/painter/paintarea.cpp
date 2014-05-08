#include <QPainter>
#include <QLabel>
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
        paintNodeTree->push_back((*i)->convertToPaintNode());
    }
}

void PaintArea::paintDocument(QPainter *qPainter)
{
    /*
     * This is the old (test) version of this function.
     * As soon as the new one works at all, this one is going away.
     * I'm just leaving it here as an example of how these
     * functions should be used.
    QString test = "Hello world! I'm just going to type a lot of words here to show how text wrapping works when "
            "implemented using Qt's library. It's much more efficient than my hard-coded algorithm!";
    QRect textDimensions(0, 0, 100, 100);
    qPainter->drawText(this->geometry(), Qt::TextWordWrap, test, &textDimensions);

    //Right now, this returns the wrong value for the bounding rectangle. As part of the rewrite, I'll
    //need to implement a coordinate system into the painter, so this should be fixed before release.
    this->setMinimumHeight(textDimensions.height());
    */

    for (std::vector<PaintNode*>::iterator i = paintNodeTree->begin();
         i != paintNodeTree->end(); i++)
    {
        (*i)->paint(qPainter, this);
    }
}

QRect PaintArea::getBoundingRectangle(PaintNode *paintNode)
{
    return QRect(0, 0, 100, 100);
}
