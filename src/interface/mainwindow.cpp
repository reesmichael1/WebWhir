#include <QMainWindow>
#include <QFileDialog>
#include <QRect>
#include <QString>
#include <QPainter>
#include <QPen>
#include "mainwindow.h"
#include "painter/painter.h"
#include "parser/htmlreader.h"

#define STARTING_X 10
#define STARTING_Y 20

MainWindow::MainWindow()
{
    reader = new HTMLReader;
    webpage = new Document;

    currentX = STARTING_X;
    currentY = STARTING_Y;
    totalWidth = 0;

    currentWeight = QFont::Normal;

    currentCharacter = new QString;

    setMinimumHeight(400);
    setMinimumWidth(600);

    setMaximumWidth(600);

    positionSet = false;

    setWindowTitle("OpenWeb 0.1 Alpha");

}

void MainWindow::setFilepath()
{
    //QString::toStdString() doesn't convert the filepath properly
    std::string filepath = QFileDialog::getOpenFileName(this,
                                                        tr("Open HTML Document")).toUtf8().constData();

    webpage = reader->prepareDocument(filepath);
}

void MainWindow::setFilepath(std::string filepath)
{
    webpage = reader->prepareDocument(filepath);
}

Document* MainWindow::getWebpage()
{
    return webpage;
}

void MainWindow::paintDocument()
{
    this->update();
}

void MainWindow::addCharacter(QString character, QFont::Weight weight)
{
    *currentCharacter = character;
    currentWeight = weight;

    updateCurrentPosition();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter qPainter(this);

    paintNodesVector = webpage->getFirstNode()->getPaintNodes();

    drawDocument(&qPainter, paintNodesVector);
}

void MainWindow::drawDocument(QPainter *qPainter, std::vector<PaintNode*> *paintNodes)
{
    std::vector<PaintNode*>::iterator i = paintNodes->begin();

    for (; i != paintNodes->end(); i++)
    {
        paintCurrentNode(*i, qPainter);
    }
}

void MainWindow::paintCurrentNode(PaintNode *currentPaintNode, QPainter *qPainter)
{
    if (currentPaintNode->getTypeOfNode() == "char")
    {

        if (positionSet)
        {
            updateCurrentPosition();
        }

        char *character = currentPaintNode->returnCharacter();
        *currentCharacter = QString(*character);


        QFont font = qPainter->font();

        if (currentPaintNode->getWeight() == QFont::Bold)
        {
            font.setBold(true);
        }
        QFontMetrics fm(font);
        QRect box(QPoint(currentX, currentY), QSize(fm.width(*character),
                                                    fm.height()));

        qPainter->setFont(font);
        qPainter->drawText(box, Qt::AlignCenter, QString(*character));

        updateCurrentPosition();
    }
    else if (currentPaintNode->getTypeOfNode() == "node")
    {
        std::vector<PaintNode*> *childPaintNodes = currentPaintNode->
                returnNode()->getPaintNodes();
        drawDocument(qPainter, childPaintNodes);
    }
}

void MainWindow::updateCurrentPosition()
{

    if (!positionSet)
    {
        QFont font;
        QFontMetrics fm(font);

        totalWidth += fm.width(*currentCharacter);
        if (totalWidth >= this->width() - 2 * STARTING_X)
        {
            currentX = STARTING_X;
            currentY += (fm.height() + 2);
            totalWidth = 0;
        }
        else
        {
            currentX += fm.width(*currentCharacter);
        }
    }

    else
    {
        currentX = STARTING_X;
        currentY = STARTING_Y;
        totalWidth = 0;
        positionSet = false;
    }
}
