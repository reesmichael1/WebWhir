/*! @class HTMLParser
 * \brief Parser for HTML input.
 *
 * This class contains a set of functions that are used to convert the
 * initial HTML input into a stack of pointers to RenderNode objects. 
 *
 * The parser is being implemented with the goal of eventual full 
 * compliance with the W3C HTML5 parser specification. See 
 * http://www.w3.org/TR/2011/WD-html5-20110113/parsing.html for more 
 * details.
 */
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "htmltokenizer.h"
#include "elements/htmlelement.h"

class HTMLParser
{
public:
    HTMLParser();
    ~HTMLParser();
    bool validateHTML(std::string htmlString);

private:
    bool hasDoctype(std::string htmlString);
    bool hasRootElement(std::string htmlString);
    /// \todo Don't forget unknown elements.
    HTMLElement* createAnElementForAToken(HTMLToken *htmlToken);
    void insertAnElementForAToken(HTMLToken *htmlToken);

    enum insertionMode {
        initial,
        beforeHtml,
        beforeHead,
        inHead,
        inHeadNoScript,
        afterHead,
        inBody,
        text,
        inTable,
        inTableText,
        inCaption,
        inColumnGroup,
        inTableBody,
        inRow,
        inCell,
        inSelect,
        inSelectInTable,
        afterBody,
        inFrameset,
        afterFrameset,
        afterAfterBody,
        afterAfterFrameset,
    };

    // Will eventually become pointers to RenderNodes
    std::vector<std::string> openElementsStack;
    insertionMode resetInsertionMode();
    std::string *headElementPointer;
    std::string *formElementPointer;
};

#endif // PARSER_H
