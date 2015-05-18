#ifndef HTMLTOKEN_H 
#define HTMLTOKEN_H

#include <string>
#include <unordered_map>

class HTMLToken {
    public:
        HTMLToken();
        void addCharacterToTokenName(char characterToAdd);
        void addCharacterToCurrentAttributeName(char characterToAdd);
        void addCharacterToCurrentAttributeValue(char characterToAdd);
        std::string getTokenName();
        bool getIsEndTagToken();
        void setIsEndTagToken(bool isEnd);
        std::unordered_map<std::string, std::string> getAttributes();
        void finalizeCurrentAttribute();

    private:
        std::string tokenName;
        std::string currentAttributeName;
        std::string currentAttributeValue;
        bool isEndTagToken;
        std::unordered_map<std::string, std::string> tokenAttributes;
};

#endif // HTMLTOKEN_H
