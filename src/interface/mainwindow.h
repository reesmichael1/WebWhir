#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include "parser/htmlreader.h"
#include "document.h"

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    void paintDocument();
    void setFilepath(std::string filepath);
    void setFilepath();
    void setMainText(std::string *textToSet);
    Document* getWebpage();

private:
    HTMLReader *reader;
    Document *webpage;
    QTextEdit *mainText;
};

#endif // MAINWINDOW_H
