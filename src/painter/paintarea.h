#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <string>

#include "document.h"

#include <QWidget>
#include <QPainter>
#include <QFont>

class PaintNode;

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    PaintArea(QWidget *parent = 0);
    ~PaintArea();
    void drawDocument(QPainter *qPainter);
    void setDocument(Document *documentToSet);
    void insertLineBreak();
    void updateCurrentPosition();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Document *webpage;
    int currentX;
    int currentY;
    int lineSpacing;
    int totalWidth;
    bool positionSet;
    bool nextWordChecked;
    bool indentOn;
    QString *currentCharacter;
    QFont currentFont;
};

#endif // PAINTAREA_H
