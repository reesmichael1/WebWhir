#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include "mainwindow.h"
#include "painter/painter.h"
#include "parser/htmlreader.h"

MainWindow::MainWindow()
{

    reader = new HTMLReader;
    webpage = new Document;

    mainText = new QTextEdit;
    mainText->setReadOnly(true);
    mainText->setMinimumHeight(400);
    mainText->setMinimumWidth(600);
    setCentralWidget(mainText);

    setWindowTitle("OpenWeb 0.1 Alpha");

}

void MainWindow::setFilepath()
{
    //QString::toStdString() doesn't convert the filepath properly
    std::string filepath = QFileDialog::getOpenFileName(this)
            .toUtf8().constData();

    webpage = reader->prepareDocument(filepath);
}

void MainWindow::setFilepath(std::string filepath)
{
    webpage = reader->prepareDocument(filepath);
}

void MainWindow::setMainText(std::string *textToSet)
{
    //QString string(*textToSet);
    mainText->setText(QString::fromStdString(*textToSet));
}

Document* MainWindow::getWebpage()
{
    return webpage;
}

void MainWindow::paintDocument()
{
    Painter painter;
    painter.setWindowToPaint(this);
    painter.paint();
}
