#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>
#include <QMenuBar>
#include <QString>
#include <QAction>
#include <QLineEdit>
#include <QScrollArea>

class PaintArea;
class HTMLReader;
class Document;
class PaintNode;

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow();
    void setFilepath(std::string filepath);
    void createActions();
    void createMenus();
    Document* getWebpage();

public slots:
    bool setFilepath();

private:
    HTMLReader *reader;
    Document *webpage;
    PaintArea *paintArea;
    bool positionSet;
    QMenu *fileMenu;
    QAction *openAct;
    QLineEdit *addressBar;
    QWidget *centralLayout;
    QScrollArea *scrollArea;
};

#endif // MAINWINDOW_H
