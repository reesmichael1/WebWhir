#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>
#include <QMenuBar>
#include <QString>
#include <QAction>
#include <QLineEdit>
#include <QScrollArea>
#include <QLabel>

class PaintArea;
class HTMLReader;
class Document;
class PaintNode;

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    bool setFilepath(std::string filepath);
    void createActions();
    void createMenus();
    void setTitle();
    Document* getWebpage();

public slots:
    bool setFilepath();

private:
    bool repaintDocument();
    bool checkFilepath(std::string filepath);
    HTMLReader *reader;
    Document *webpage;
    PaintArea *paintArea;
    bool positionSet;
    QMenu *fileMenu;
    QAction *openAct;
    QLineEdit *addressBar;
    QWidget *centralLayout;
    QScrollArea *scrollArea;
    QLabel *documentDisplay;
};

#endif // MAINWINDOW_H
