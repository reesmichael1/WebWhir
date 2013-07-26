#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>
#include <QMenuBar>
#include <QString>
#include <QAction>
#include <QLineEdit>

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
    void setFilepath();

private:
    HTMLReader *reader;
    Document *webpage;
    PaintArea *paintArea;
    bool positionSet;
    QMenu *fileMenu;
    QAction *openAct;
    QLineEdit *addressBar;
    QWidget *centralLayout;
};

#endif // MAINWINDOW_H
