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
#define STARTING_Y 10
#define LINE_SPACING 30

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

    positionSet = false;

    createActions();
    createMenus();

    setWindowTitle("WebWhirr 0.1 Beta");

}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);

    connect(openAct, SIGNAL(triggered()), this, SLOT(setFilepath()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
}

void MainWindow::setFilepath(std::string filepath)
{
    //Construct a Document (contains node tree) from parsing document
    //passed from command line.
    webpage = reader->prepareDocument(filepath);
}

void MainWindow::setFilepath()
{
    //Delete any old nodes to avoid memory leaks.
    if (webpage->getFirstNode() != NULL)
    {
        webpage->clearTree();
    }

    //QString::toStdString() doesn't convert the filepath properly
    std::string filepath = QFileDialog::getOpenFileName(this,
                                                        tr("Open HTML Document")).toUtf8().constData();

    //Construct a Document (contains node tree) from parsing document
    //selected in "Open HTML Document" dialog.
    webpage = reader->prepareDocument(filepath);

    //Repaint the window to show the selected document
    //(necessary to open new documents).
    this->update();
}

Document* MainWindow::getWebpage()
{
    return webpage;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //Draw the document (this will be split off into Painter soon).
    Q_UNUSED(event);

    if (webpage->getFirstNode() != NULL)
    {

        QPainter qPainter(this);
        paintNodesVector = webpage->getFirstNode()->getPaintNodes();
        drawDocument(&qPainter, paintNodesVector);

        //Prevents document from moving around while being redrawn.
        positionSet = true;
    }
}

void MainWindow::drawDocument(QPainter *qPainter,
                              std::vector<PaintNode*> *paintNodes)
{
    std::vector<PaintNode*>::iterator i = paintNodes->begin();

    for (; i != paintNodes->end(); i++)
    {
        paintCurrentNode(*i, qPainter);
    }
}

void MainWindow::insertLineBreak()
{
    currentX = STARTING_X;
    currentY += LINE_SPACING;
    totalWidth = 0;
}

void MainWindow::paintCurrentNode(PaintNode *currentPaintNode,
                                  QPainter *qPainter)
{
    if (currentPaintNode->getTypeOfPaintNode() == "char")
    {
        //Draw the text contained within each paragraph node. New lines are
        //only added after each paragraph node--not any other element.
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
        else
        {
            font.setBold(false);
        }
        QFontMetrics fm(font);
        QRect box(QPoint(currentX, currentY), QSize(fm.width(*character),
                                                    fm.height()));

        qPainter->setFont(font);
        qPainter->drawText(box, Qt::AlignCenter, QString(*character));

        updateCurrentPosition();
    }

    else if (currentPaintNode->getTypeOfPaintNode() == "node")
    {
        //Call the function again on each of the PaintNode's child paint nodes.
        //This ensures that all of the child nodes of the overall parent node
        //are drawn.
        std::vector<PaintNode*> *childPaintNodes = currentPaintNode->
                returnNode()->getPaintNodes();
        drawDocument(qPainter, childPaintNodes);
        if (currentPaintNode->returnNode()->getTypeOfRenderNode() == "p")
        {
            insertLineBreak();
        }
    }
}

//This adjusts the location where the next character will be drawn, including
//changing lines when the total length exceeds the width of the window.
void MainWindow::updateCurrentPosition()
{

    if (!positionSet)
    {
        QFont font;
        QFontMetrics fm(font);

        totalWidth += fm.width(*currentCharacter);

        //3 is a totally random number, chosen because it looks good.
        if (totalWidth >= this->width() - 3 * STARTING_X)
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
