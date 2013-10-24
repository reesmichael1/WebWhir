#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include "mainwindow.h"
#include "parser/htmlreader.h"
#include "painter/paintarea.h"

#define WINDOW_STARTING_HEIGHT 400
#define WINDOW_STARTING_WIDTH 600

QString versionTitle = "WebWhirr 0.2.0 Beta";

MainWindow::MainWindow()
{
    reader = new HTMLReader;
    webpage = new Document;

    //Draw main window for WebWhirr.
    this->setGeometry(0, 0, WINDOW_STARTING_WIDTH, WINDOW_STARTING_HEIGHT);

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

    centralLayout = new QWidget(this);
    centralLayout->setLayout(layout);

    setCentralWidget(centralLayout);

    createActions();
    createMenus();

    setWindowTitle(versionTitle);

}

MainWindow::~MainWindow()
{
    //Everything else is cleared elsewhere
    //or handled by Qt's memory management.
    if (webpage->getFirstNode() != NULL)
    {
        delete reader;
    }
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

bool MainWindow::setFilepath(std::string filepath)
{
    if (!checkFilepath(filepath))
    {
        return false;
    }
    else
    {
        //Construct a Document (contains node tree) from parsing document
        //passed from command line.
        webpage = reader->prepareDocument(filepath);
        addressBar->setText(QString::fromStdString(filepath));

        setTitle();

        paintArea->setDocument(webpage);
    }

    return true;
}

bool MainWindow::setFilepath()
{
    //QString::toStdString() doesn't convert the filepath properly
    std::string filepath = QFileDialog::getOpenFileName(this,
                       tr("Open HTML Document")).toUtf8().constData();
    if (filepath.empty())
    {
        return false;
    }

    if (!checkFilepath(filepath))
    {
        QMessageBox invalidTypeErrorBox;
        invalidTypeErrorBox.
                setText("Error: Document type is invalid or not supported.");
        invalidTypeErrorBox.exec();
        return false;
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
        setTitle();

        paintArea->setDocument(webpage);

        return repaintDocument();
    }
}

void MainWindow::setTitle()
{
    if (webpage->getDocumentTitle() != "")
    {
        QString titleString = versionTitle + " -- ";
        titleString += QString::fromStdString(webpage->getDocumentTitle());
        this->setWindowTitle(titleString);
    }

    else
    {
        this->setWindowTitle(versionTitle);
    }
}

bool MainWindow::repaintDocument()
{
    std::vector<RenderNode*> renderNodeTree =
            *webpage->getFirstNode()->getChildNodes();
    paintArea->constructPaintNodeTree(renderNodeTree);

    paintArea->update();
    return true;
}

bool MainWindow::checkFilepath(std::string filepath)
{
    //This is a fix for the crash on opening a non-HTML document.
    //It will have to do until I write a check into the encoding,
    //because for some reason a similar check in the document text
    //itself always returns true.
    if (filepath.find(".html") != std::string::npos ||
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
