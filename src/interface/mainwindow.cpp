#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QBoxLayout>
#include <QLabel>
#include <QMessageBox>

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

    paintArea = new PaintArea(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(paintArea);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(addressBarLayout);
    layout->addWidget(scrollArea);

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

bool MainWindow::setFilepath()
{
    //QString::toStdString() doesn't convert the filepath properly
    std::string filepath = QFileDialog::getOpenFileName(this,
                                                        tr("Open HTML Document")).toUtf8().constData();

    if (!checkFilepath(filepath))
    {
        if (webpage->getFirstNode() == NULL)
        {
            return false;
        }

        else
        {
            QMessageBox invalidTypeErrorBox;
            invalidTypeErrorBox.setText("Error: Document type is invalid or not supported.");
            invalidTypeErrorBox.exec();
            return false;
        }
    }

    else
    {
        //Delete any old nodes to avoid memory leaks.
        if (webpage->getFirstNode() != NULL)
        {
            webpage->clearTree();
        }

        addressBar->setText(QString::fromStdString(filepath));


        //Construct a Document (contains node tree) from parsing document
        //selected in "Open HTML Document" dialog.
        webpage = reader->prepareDocument(filepath);

        paintArea->setDocument(webpage);

        //Repaint the window to show the selected document
        //(necessary to open new documents).
        //this->update();
        paintArea->update();
        return true;


    }
}

bool MainWindow::checkFilepath(std::string filepath)
{
    //This is a fix for the crash on opening a non-HTML document.
    //It will have to do until I write a check into the encoding,
    //because for some reason a similar check in the document text
    //itself always returns true.
    if (filepath.find(".html") != std::string::npos &&
            filepath.find(".htm") != std::string::npos)
    {
        return true;
    }

    return false;
}

Document* MainWindow::getWebpage()
{
    return webpage;
}
