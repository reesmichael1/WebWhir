#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>
#include <QPainter>
#include <QString>

class Painter;
class HTMLReader;
class Document;
class PaintNode;

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    void addCharacter(QString character, QFont::Weight weight = QFont::Normal);
    void paintDocument();
    void setFilepath(std::string filepath);
    void setFilepath();
    void setMainText(std::string *textToSet);
    void drawDocument(QPainter *qPainter);
    void drawDocument(QPainter *qPainter, std::vector<PaintNode*> *paintNodes);
    void paintCurrentNode(PaintNode *currentPaintNode, QPainter *qPainter);
    Document* getWebpage();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    void updateCurrentPosition();
    HTMLReader *reader;
    Document *webpage;
    QString *currentCharacter;
    Painter *painter;
    QFont::Weight currentWeight;
    int currentX;
    int currentY;
    int totalWidth;
    std::vector<PaintNode*> *paintNodesVector;
    bool positionSet;
};

#endif // MAINWINDOW_H
