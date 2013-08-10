#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include "mainwindow.h"
#include "parser/htmlreader.h"
#include "painter/paintarea.h"

#define WINDOW_HEIGHT 480

MainWindow::MainWindow()
{
    reader = new HTMLReader;
    webpage = new Document;

    //Draw main window for WebWhirr.
    setMinimumHeight(WINDOW_HEIGHT);
    setMaximumHeight(WINDOW_HEIGHT);

    positionSet = false;

    QLabel *addressBarLabel = new QLabel(tr("Current Document:"));
    addressBar = new QLineEdit;
    addressBar->setReadOnly(true);

    QHBoxLayout *addressBarLayout = new QHBoxLayout;
    addressBarLayout->addWidget(addressBarLabel);
    addressBarLayout->addWidget(addressBar);

    paintArea = new PaintArea;
    scrollArea = new QScrollArea(this);
    documentDisplay = new QLabel(scrollArea);

    documentDisplay->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    scrollArea->setWidget(documentDisplay);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(addressBarLayout);
    layout->addWidget(scrollArea);

    centralLayout = new QWidget;
    centralLayout->setLayout(layout);

    setCentralWidget(centralLayout);

    createActions();
    createMenus();

    setWindowTitle("WebWhirr 0.1.0");

}

MainWindow::~MainWindow()
{
    //Everything else is cleared elsewhere
    //or handled by Qt's memory management.
    delete reader;
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
        invalidTypeErrorBox.setText("Error: Document type is invalid or not supported.");
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

        paintArea->setDocument(webpage);

        return repaintDocument();
    }
}

//This entire function is a mess. I will return and work
//on it more after the 0.1.0 release.
bool MainWindow::repaintDocument()
{
    //Paint the current document in paintArea by creating a QPixmap
    //and assigning this to the QLabel documentDisplay. Dimensions
    //are also set to avoid annoying issues with the scrollbars.
    QPixmap paintedDocument;

    //grab() has to be called twice. Otherwise, the pixmap is the wrong
    //size when the document is first displayed and the document has to
    //be opened twice in order to scroll through it properly.
    paintedDocument = paintArea->grab();
    paintedDocument.scaled(paintArea->size(), Qt::IgnoreAspectRatio);
    paintedDocument = paintArea->grab();

    documentDisplay->setMinimumWidth(paintedDocument.width());
    documentDisplay->setMaximumWidth(paintedDocument.width());
    documentDisplay->setMaximumHeight(paintArea->height());

    documentDisplay->setPixmap(paintedDocument);
    scrollArea->setMinimumWidth(documentDisplay->width() + 20);
    this->setMinimumWidth(scrollArea->width() + 20);
    this->setMaximumWidth(scrollArea->width() + 20);

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
