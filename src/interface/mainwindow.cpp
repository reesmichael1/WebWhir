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

    painter = new Painter(this);

    currentWeight = QFont::Normal;

    reader->setPainter(painter);

    currentCharacter = new QString;

    setMinimumHeight(400);
    setMinimumWidth(600);

    setMaximumHeight(400);
    setMaximumWidth(600);

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
    painter->paintWebpage(webpage);
}

void MainWindow::addCharacter(QString character, QFont::Weight weight)
{
    *currentCharacter = character;

    currentWeight = weight;

    this->repaint();
    updateCurrentPosition();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter qPainter(this);
    drawDocument(&qPainter);
}

void MainWindow::drawDocument(QPainter *qPainter)
{
    QFont font = qPainter->font();
    if (currentWeight == QFont::Bold)
    {
        font.setBold(true);
    }
    else
    {
        font.setBold(false);
    }
    QFontMetrics fm(font);
    QRect box;
    box.setCoords(currentX, currentY + fm.height(), currentX +
                  fm.width(*currentCharacter), currentY + fm.height());
    box.setWidth(fm.width(*currentCharacter));
    box.setHeight(fm.height());

    qPainter->drawText(box, Qt::AlignCenter, *currentCharacter);
}

void MainWindow::updateCurrentPosition()
{
    QFont font;
    QFontMetrics fm(font);

    totalWidth += fm.width(*currentCharacter);
    if (totalWidth >= this->width() - STARTING_X)
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
