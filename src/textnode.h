#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "rendernode.h"

class TextNode : public RenderNode
{
public:
    TextNode();
    void setText(std::string textToSet);
    void setCharacterColor(sf::Color colorToSet);
    void setTextBackgroundColor(sf::Color colorToSet);
    void setTextCharacterSize(int size);
    sf::Color getCharacterColor();
    sf::Color getTextBackgroundColor();
    int getTextCharacterSize();
    virtual std::string getText();

private:
    std::string text;
    int textCharacterSize;
    sf::Color textCharacterColor;
    sf::Color textBackgroundColor;

};

#endif // TEXTNODE_H
