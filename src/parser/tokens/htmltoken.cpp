/*! \file 
 * \brief Implement HTMLToken objects (emitted by the HTMLTokenizer).
 *
 * An HTMLToken is an object that the tokenizer builds as the HTML input is 
 * parsed, and then the parser stores the information that the HTML
 * contains within the token. 
 */
#include "htmltoken.h"

/*!
 * \brief Constructor for the HTMLToken class.
 *
 * Construct an HTMLToken. By default, the tokens are set to not be end 
 * tag tokens.
 */
HTMLToken::HTMLToken()
{
    isEndTagToken = false;
}

/// \brief Check if the token is an end tag token.
/// \return bool: true if the token is an end tag token, false otherwise
bool HTMLToken::getIsEndTagToken()
{
    return isEndTagToken;
}

/// \brief Set whether or not the token is an end tag token.
/// \return void
void HTMLToken::setIsEndTagToken(bool isEnd)
{
    isEndTagToken = isEnd;
}

/// \brief Add \a characterToAdd to the name of the token.
/// \return void
void HTMLToken::addCharacterToTokenName(char characterToAdd)
{
    tokenName += characterToAdd;
}

/// \brief Add \a characterToAdd to the current attribute in scope's name.
/// \return void
void HTMLToken::addCharacterToCurrentAttributeName(char characterToAdd)
{
    currentAttributeName += characterToAdd;
}

/// \brief Add \a characterToAdd to the current attribute in scope's value.
/// \return void
void HTMLToken::addCharacterToCurrentAttributeValue(char characterToAdd)
{
    currentAttributeValue += characterToAdd;
}

/// \brief Get the name of the current token.
/// \return std::string: the name of the token
std::string HTMLToken::getTokenName()
{
    return tokenName;
}

/*!  
 * \brief Get a std::unordered_map of the token's attributes.
 *
 * \return std::unordered_map<std::string, std::string>: a map in which the
 * key is the name of an attribute and the value is the value of that 
 * attribute
 */
std::unordered_map<std::string, std::string> HTMLToken::getAttributes()
{
    return tokenAttributes;
}

/*!
 * \brief Finish building the current attribute and move on to the next.
 *
 * When the attribute is being built, characters are added individually to
 * the attribute's name and value. Once an attribute has been completed, 
 * the temporary variables that have stored the name and value are stored
 * in the attribute map, and then the temporary variables are cleared. 
 *
 * \return void
 */
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
