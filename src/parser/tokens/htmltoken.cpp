#include "htmltoken.h"

HTMLToken::HTMLToken()
{
    isEndTagToken = false;
}

bool HTMLToken::getIsEndTagToken()
{
    return isEndTagToken;
}

void HTMLToken::setIsEndTagToken(bool isEnd)
{
    isEndTagToken = isEnd;
}

void HTMLToken::addCharacterToTokenName(char characterToAdd)
{
    tokenName += characterToAdd;
}

void HTMLToken::addCharacterToCurrentAttributeName(char characterToAdd)
{
    currentAttributeName += characterToAdd;
}

void HTMLToken::addCharacterToCurrentAttributeValue(char characterToAdd)
{
    currentAttributeValue += characterToAdd;
}

std::string HTMLToken::getTokenName()
{
    return tokenName;
}

std::unordered_map<std::string, std::string> HTMLToken::getAttributes()
{
    return tokenAttributes;
}

void HTMLToken::finalizeCurrentAttribute()
{
    if (tokenAttributes.find(currentAttributeName) == tokenAttributes.end())
    {
        tokenAttributes.insert({currentAttributeName, 
                currentAttributeValue});
    }
    currentAttributeName = "";
    currentAttributeValue = "";
}
