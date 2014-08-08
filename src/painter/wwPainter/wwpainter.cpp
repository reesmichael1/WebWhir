#include "wwpainter.h"

WWPainter::WWPainter(QPaintDevice *parent) : QPainter(parent)
{
}

void WWPainter::drawInlineText(int xOffset, int y, int width, int height, QString text)
{
    QStringList words = text.split(" ");

    QString restOfLine = "";
    QString restOfWords = "";
    bool wrapped = false;
    for (int i = 0; i < words.size() - 1; i++)
    {
        QString word = words.at(i);
        if (this->boundingRect(QRect(xOffset, y, width,
                       height), restOfLine + word).width() >
                       (width - xOffset))
        {
            this->drawText(QRect(xOffset, 0, width - xOffset,
                                 height), restOfLine);
            for (int j = 0; j < i; j++)
            {
                words.removeAt(0);
            }

            restOfWords = words.join(" ");
            wrapped = true;
            break;
        }
        else
        {
            restOfLine += (word + " ");
        }
    }

    if (wrapped)
    {
        int yCoordinate = QFontMetrics(this->font()).lineSpacing();
        this->drawText(QRect(0, yCoordinate, width,
                height),
               restOfWords);
    }
    else
    {
        /*
        this->drawText(QRect(0, 0, width,
                height), "");
                */
        // Populate yCoordinate from Layout.
        int yCoordinate = 0;
        this->drawText(QRect(xOffset, yCoordinate + y, width - xOffset,
                height), restOfLine);
    }
}
