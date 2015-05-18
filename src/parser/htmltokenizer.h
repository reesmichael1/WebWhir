#ifndef HTMLTOKENIZER
#define HTMLTOKENIZER

#include <string>
#include "tokens/htmltoken.h"

class HTMLTokenizer {
public:
    HTMLTokenizer();
    HTMLToken emitNextToken(std::string htmlString, int startCharacter);

private:
    // Ignoring RCDATA and script states for now
    enum class tokenizerState {
        dataState,
        charRefInDataState,
        rawTextState,
        scriptDataState,
        plainTextState,
        tagOpenState,
        endTagOpenState,
        tagNameState,
        rawTextLessThanSignState,
        rawTextEndTagOpenState,
        rawTextEndTagNameState,
        beforeAttributeNameState,
        attributeNameState,
        afterAttributeNameState,
        beforeAttributeValueState,
        attributeValueDoubleQuotedState,
        attributeValueSingleQuotedState,
        attributeValueUnquotedState,
        charRefInAttributeValueState,
        afterAttributeValueQuotedState,
        selfClosingStartTagState,
        bogusCommentState,
        markupDeclarationOpenState,
        commentStartState,
        commentStartDashState,
        commentState,
        commentEndDashState,
        commentEndState,
        commentEndBangState,
        doctypeState,
        beforeDoctypeNameState,
        doctypeNameState,
        afterDoctypeNameState,
        // For now, only reading <!doctype html> 
    };
    tokenizerState currentState;
};

#endif // HTMLTOKENIZER
