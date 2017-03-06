/*! \file
 * \brief Create HTMLToken objects. 
 */
#include "htmltokenizer.h"

/// \todo Correctly handle parse errors

/*! 
 *
 * \brief Construct the HTMLTokenizer class.
 *
 * Initialize the HTMLTokenizer. As defined in the W3C parser specification,
 * the tokenizer state is initially set to the data state.
 */
HTMLTokenizer::HTMLTokenizer()
{
    currentState = tokenizerState::dataState;
}

/*!
 * \brief Emit the HTMLToken in \a htmlString starting at \a startCharacter.
 *
 * Emit the HTMLToken that corresponds to the HTML tag beginning at
 * \a startCharacter in \a htmlString. 
 *
 * \return HTMLToken: The HTMLToken that should be created by the tokenizer
 * at \a startCharacter in \a htmlString.
 */

/// \todo Many more states to handle
HTMLToken HTMLTokenizer::emitNextToken(std::string htmlString, 
        int startCharacter)
{
    // Start with -1 because of +1 on first run of loop
    int characterIndex = startCharacter - 1;
    HTMLToken currentToken;
    while (true)
    {
        characterIndex += 1;
        char nextCharacter = htmlString[characterIndex];
        if (currentState == tokenizerState::dataState)
        {
            if (nextCharacter == '&')
            {
                currentState = tokenizerState::charRefInDataState;
            }
            if (nextCharacter == '<')
            {
                currentState = tokenizerState::tagOpenState;
            }
            else
            {
                // TODO: Convert uppercase to lowercase
                currentToken.addCharacterToTokenName(nextCharacter); 
                //std::string(1, nextCharacter);
                return currentToken;
            }

            // NULL: parse error
            // EOF: Emit end-of-file token
            continue;
        }
        // if (currentState == tokenizerState::charRefInDataState)
        if (currentState == tokenizerState::tagOpenState)
        {
            if (nextCharacter == '!')
            {
                currentState = tokenizerState::markupDeclarationOpenState;
            }
            else if (nextCharacter == '/')
            {
                currentState = tokenizerState::endTagOpenState;
            }
            else
            {
                currentState = tokenizerState::tagNameState;
                // TODO: convert uppercase to lowercase if necessary
                currentToken.addCharacterToTokenName(nextCharacter);
            }
            // ?: parse error, go to bogus comment state
            // Anything else: parse error
            continue;
        }
        if (currentState == tokenizerState::endTagOpenState)
        {
            currentToken.setIsEndTagToken(true);

            if (isalpha(nextCharacter))
            {
                // TODO: convert uppercase to lowercase if necessary
                currentToken.addCharacterToTokenName(nextCharacter);
                currentState = tokenizerState::tagNameState;
            }
            // Anything else: parse error
            continue;
        }
        if (currentState == tokenizerState::tagNameState)
        {
            if (isspace(nextCharacter))
            {
                currentState = tokenizerState::beforeAttributeNameState;
            }
            if (nextCharacter == '>')
            {
                currentState = tokenizerState::dataState;
                return currentToken;
            }
            if (isalpha(nextCharacter))
            {
                // TODO: convert uppercase to lowercase if necessary
                currentToken.addCharacterToTokenName(nextCharacter);
            }
            // NULL, EOF: parse error
            continue;
        }
        if (currentState == tokenizerState::beforeAttributeNameState)
        {
            if (isspace(nextCharacter)) 
                continue;
            else if (nextCharacter == '/')
            {
                currentState = tokenizerState::selfClosingStartTagState;
            }
            else if (nextCharacter == '>')
            {
                currentState = tokenizerState::dataState;
                return currentToken;
            }
            else
            {
                // TODO: convert uppercase to lowercase if necessary
                currentToken.addCharacterToCurrentAttributeName(
                        nextCharacter);
                currentState = tokenizerState::attributeNameState;
            }
            // anything else: parse error (EOF treated differently)
            continue;
        }
        if (currentState == tokenizerState::attributeNameState)
        {
            // TODO: Check for duplicate attribute names
            if (isspace(nextCharacter))
            {
                currentState = tokenizerState::afterAttributeNameState;
            }
            else if (nextCharacter == '/')
            {
                currentState = tokenizerState::selfClosingStartTagState;
            }
            else if (nextCharacter == '=')
            {
                currentState = tokenizerState::beforeAttributeValueState;
            }
            else if (nextCharacter == '>')
            {
                currentState = tokenizerState::dataState;
                return currentToken;
            }
            else 
            {
                // TODO: Convert uppercase to lowercase if necessary
                currentToken.
                    addCharacterToCurrentAttributeName(nextCharacter);
            }
            continue;
            // Anything else: parse error
        }
        if (currentState == tokenizerState::afterAttributeNameState)
        {
            if (isspace(nextCharacter)) continue;

            if (nextCharacter == '\"')
            {
                currentState = 
                    tokenizerState::attributeValueDoubleQuotedState;
            }
            else if (nextCharacter == '&')
            {
                currentState = tokenizerState::attributeValueUnquotedState;
            }
            else if (nextCharacter == '\'')
            {
                currentState = 
                    tokenizerState::attributeValueSingleQuotedState;
            }
            // Various parse errors
            else
            {
                currentToken.
                    addCharacterToCurrentAttributeValue(nextCharacter);
                currentState = tokenizerState::attributeValueUnquotedState;
            }
        }
        if (currentState == tokenizerState::beforeAttributeValueState)
        {
            if (isspace(nextCharacter)) continue;

            else if (nextCharacter == '\"')
            {
                currentState = 
                    tokenizerState::attributeValueDoubleQuotedState;
            }
            else if (nextCharacter == '&')
            {
                currentState = tokenizerState::attributeValueUnquotedState;
            }
            else if (nextCharacter == '\'')
            {
                currentState = 
                    tokenizerState::attributeValueSingleQuotedState;
            }
            else 
            {
                currentToken.
                    addCharacterToCurrentAttributeValue(nextCharacter);
                currentState = tokenizerState::attributeValueUnquotedState;
            }
            continue;
        }
        if (currentState == 
                tokenizerState::attributeValueDoubleQuotedState)
        {
            if (nextCharacter == '\"')
            {
                currentState = 
                    tokenizerState::afterAttributeValueQuotedState;
            }
            else if (nextCharacter == '&')
            {
                // Allowed character: "
                currentState = tokenizerState::charRefInAttributeValueState;
            }
            // NULL, EOF: Parse error
            else
            {
                currentToken.
                    addCharacterToCurrentAttributeValue(nextCharacter);
            }
            continue;
        }
        if (currentState == 
                tokenizerState::attributeValueSingleQuotedState)
        {
            if (nextCharacter == '\'')
            {
                currentState = 
                    tokenizerState::afterAttributeValueQuotedState;
            }
            else if (nextCharacter == '&')
            {
                // Extra allowed character: '
                currentState = 
                    tokenizerState::charRefInAttributeValueState;
            }
            // NULL, EOF: Parse error
            else
            {
                currentToken.
                    addCharacterToCurrentAttributeValue(nextCharacter);
            }
            continue;
        }
        if (currentState == tokenizerState::attributeValueUnquotedState)
        {
            if (isspace(nextCharacter))
            {
                currentState = tokenizerState::beforeAttributeNameState;
            }
            else if (nextCharacter == '&')
            {
                // Extra allowed character: &
                currentState = tokenizerState::charRefInAttributeValueState;
            }
            else if (nextCharacter == '>')
            {
                currentState = tokenizerState::dataState;
                return currentToken;
            }
            // Lots of characters: parse error
            else
            {
                currentToken.
                    addCharacterToCurrentAttributeValue(nextCharacter);
            }
        }
        if (currentState == 
                tokenizerState::afterAttributeValueQuotedState)
        {
            currentToken.finalizeCurrentAttribute();
            if (isspace(nextCharacter))
            {
                currentState = tokenizerState::beforeAttributeNameState;
            }
            if (nextCharacter == '/')
            {
                currentState = tokenizerState::selfClosingStartTagState;
            }
            if (nextCharacter == '>')
            {
                currentState = tokenizerState::dataState;
                return currentToken;
            }
            // anything else: parse error
            continue;
        }
    }
}
