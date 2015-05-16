#ifndef HTMLTOKENIZER
#define HTMLTOKENIZER

#include <string>

class HTMLTokenizer {
public:
    std::string emitNextToken(std::string htmlString, int startCharacter);

private:
    // Ignoring RCDATA and script states for now
    enum class tokenizerState {
        dataState,
        charRefInDataState,
        charRefInRcDataState,
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
};

#endif // HTMLTOKENIZER
