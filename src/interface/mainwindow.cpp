#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QBoxLayout>
#include <QLabel>

#include "mainwindow.h"
#include "parser/htmlreader.h"
#include "painter/paintarea.h"

MainWindow::MainWindow()
{
    reader = new HTMLReader;
    webpage = new Document;

    setMinimumHeight(400);
    setMinimumWidth(600);

    positionSet = false;

    QLabel *addressBarLabel = new QLabel(tr("Current Document:"));
    addressBar = new QLineEdit;
    addressBar->setReadOnly(true);

    QHBoxLayout *addressBarLayout = new QHBoxLayout;
    addressBarLayout->addWidget(addressBarLabel);
    addressBarLayout->addWidget(addressBar);

    paintArea = new PaintArea;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(addressBarLayout);
    layout->addWidget(paintArea);

    centralLayout = new QWidget;
    centralLayout->setLayout(layout);

    setCentralWidget(centralLayout);

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
    addressBar->setText(QString::fromStdString(filepath));

    paintArea->setDocument(webpage);
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
    addressBar->setText(QString::fromStdString(filepath));

    //Construct a Document (contains node tree) from parsing document
    //selected in "Open HTML Document" dialog.
    webpage = reader->prepareDocument(filepath);

    paintArea->setDocument(webpage);

    //Repaint the window to show the selected document
    //(necessary to open new documents).
    this->update();
}

Document* MainWindow::getWebpage()
{
    return webpage;
}
