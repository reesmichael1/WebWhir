#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QMainWindow>
#include <QPainter>
#include <QString>

class Painter;
class HTMLReader;
class Document;

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    void addCharacter(QString character);
    void paintDocument();
    void setFilepath(std::string filepath);
    void setFilepath();
    void setMainText(std::string *textToSet);
    void drawDocument();
    Document* getWebpage();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    void updateCurrentPosition();
    HTMLReader *reader;
    Document *webpage;
    QString *currentCharacter;
    Painter *painter;
    QPainter *qPainter;
    int currentX;
    int currentY;
    int totalWidth;
};

#endif // MAINWINDOW_H
