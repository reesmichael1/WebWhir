#ifndef PAINTAREA_H
#define PAINTAREA_H

#include "document.h"

#include <QWidget>
#include <QPainter>
#include <QFont>

class PaintNode;

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);
    void drawDocument(QPainter *qPainter);
    void drawDocument(QPainter *qPainter, std::vector<PaintNode*> *paintNodes);
    void paintCurrentNode(PaintNode *currentPaintNode, QPainter *qPainter, std::vector<PaintNode *> *paintNodes);
    void setDocument(Document *documentToSet);
    void insertLineBreak();
    void updateCurrentPosition();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    int getNextWordWidth(std::vector<PaintNode *> *paintNodes, QPainter *qPainter);
    Document *webpage;
    int currentX;
    int currentY;
    int lineSpacing;
    int totalWidth;
    bool positionSet;
    bool nextWordChecked;
    QString *currentCharacter;
    QFont currentFont;
    std::vector<PaintNode*> *paintNodesVector;
};

#endif // PAINTAREA_H
