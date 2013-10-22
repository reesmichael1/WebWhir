#include "paintarea.h"

PaintArea::PaintArea()
{
    paintNodeTree = new std::vector<PaintNode*>;
}

void PaintArea::setDocument(Document *documentToSet)
{
    webpage = documentToSet;
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void PaintArea::constructPaintNodeTree(std::vector<RenderNode*>
                                       renderNodeTree)
{
    //Somehow, this should create a tree of PaintNodes. I haven't decided
    //what the best way to approach this is yet.
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
