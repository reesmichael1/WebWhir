/*! \file htmlparser.cpp
 * \brief This file implements the HTMLParser.
 *
 * This file contains functions that make up the HTMLParser. It validates,
 * parses, and tokenizes the HTML and creates a stack of RenderNodes as
 * a result.
 *
 * To use the HTMLParser, construct an instance. Parsing methods will
 * follow soon is not yet implemented in the current iteration.
 */
#include <QString>
#include <QStringList>

#include "htmlparser.h"

/// \todo Determine character encoding

/*!
 * \brief Constructor for the HTMLParser class.
 *
 * Construct the HTMLParser. In compliance with the W3C HTML parsing
 * algorithm, a headElementPointer and a formElementPointer are created
 * and initialized to null. Both of these are points to RenderNode objects.
 */
HTMLParser::HTMLParser()
{
    headElementPointer = new std::string;
    formElementPointer = new std::string;
}

/*!
 * \brief Destructor for the HTMLParser class.
 *
 * Destruct an instance of HTMLParser. This removes the pointers to the 
 * head and form HTMLElement objects.
 */
HTMLParser::~HTMLParser()
{
    delete headElementPointer;
    delete formElementPointer;
}

/*! 
 * \brief Check that the given std::string \a htmlString conforms to
 * the HTML syntax.
 *
 * Check that the given document conforms to the HTML syntax. Effectively, 
 * this involves verifying that the HTML has a root element and a doctype,
 * and that no non-space characters occur outside of an HTML element.
 *
 * This function returns a boolean: true if \a htmlString is valid HTML and
 * false otherwise.
 *
 * See http://dev.w3.org/html5/spec-preview/syntax.html#syntax for more 
 * details. 
 *
 * \return bool
 */
bool HTMLParser::validateHTML(std::string htmlString)
{
    /// \todo Check that no non-space characters occur outside of a tag.
    return hasRootElement(htmlString) && hasDoctype(htmlString);
}

/*! \brief Verify that \a htmlString has a doctype.
 *
 * Check that the given std::string \a htmlString contains a valid doctype 
 * before the root <html> element. A description of a valid doctype can be 
 * found at 
 * http://www.w3.org/TR/2011/WD-html5-20110113/syntax.html#syntax-doctype. 
 *
 * For now, WebWhirr only supports the !html doctype.
 *
 * \return bool
 */
bool HTMLParser::hasDoctype(std::string htmlString)
{
    // If we've gotten this far, the string has a root html element
    int rootIndex = htmlString.find("<html>");
    std::string preamble = htmlString.substr(0, rootIndex);

    while (preamble.length() > 0)
    {
        int start = preamble.find("<");
        int end = preamble.find(">");
        if (preamble.find(">") == std::string::npos) return false;
        std::string tag = preamble.substr(start + 1, end - 1);
        if (tag[0] == '!')
        {
            // My preference is to avoid using Qt objects
            // except in the interface, so I may change this
            QString tagQString = QString::fromStdString(tag).simplified();
            QStringList words = tagQString.split(' ');
            // For now, I'm going to ignore 
            // the optional doctype legacy string
            if ((QString::compare(words.at(0), "!DOCTYPE", 
                        Qt::CaseInsensitive) == 0) &&
                (QString::compare(words.at(1), "html", 
                      Qt::CaseInsensitive) == 0))
            {
                return true;
            }
        }
        preamble = preamble.substr(end + 1);
    }

    return false;
}

/*! \brief Check if the root <html> element is in the document.
 *
 * Check if the given std::string \a htmlString contains the substrings
 * <html> and </html>. This is not the cleanest implementation, and needs
 * to be revised.
 *
 * \return bool
 *
 * \todo Improve implementation of checking for root element.
 */
bool HTMLParser::hasRootElement(std::string htmlString)
{
    int startIndex = htmlString.find("<html>");
    int endIndex = htmlString.find("</html>");
    if (htmlString.find("<html>") == std::string::npos 
            || htmlString.find("</html>") == std::string::npos) 
        return false;
    return endIndex > startIndex;
}

/*! \brief Determine the correct insertion mode for the parser.
 *
 * The HTMLParser uses an insertionMode to know what to do when. The 
 * insertionMode determines how different characters should be treated at
 * different points in the parsing stage. Here, the insertion mode is 
 * determined as defined in the algorithm described at
 * http://www.w3.org/TR/2011/WD-html5-20110113/parsing.html#the-insertion-mode.
 * \return HTMLParser::insertionMode
 */
HTMLParser::insertionMode HTMLParser::resetInsertionMode()
{
    bool onLastNode = false;
    int lastNodePosition = openElementsStack.size() - 1;
    std::string lastNode = openElementsStack.at(lastNodePosition);

    while (true)
    {
        if (openElementsStack.size() == 1)
        {
            onLastNode = true;
            //lastNode = "context"; Will only give good HTML for now
        }
        if (lastNode == "select")
        {
            return inSelect;
        }
        if ((lastNode == "td" || lastNode == "th") && !onLastNode)
        {
            return inRow;
        }
        if (lastNode == "tr")
        {
            return inRow;
        }
        if (lastNode == "tbody" || lastNode == "thead" || 
                lastNode == "tfoot")
        {
            return inTableBody;
        }
        if (lastNode == "caption")
        {
            return inCaption;
        }
        if (lastNode == "colgroup")
        {
            return inColumnGroup;
        }
        if (lastNode == "table")
        {
            return inTable;
        }
        if (lastNode == "head")
        {
            return inBody;
        }
        if (lastNode == "body")
        {
            return inBody;
        }
        if (lastNode == "frameset")
        {
            return inFrameset;
        }
        if (lastNode == "html")
        {
            return beforeHead;
        }
        if (onLastNode)
        {
            return inBody;
        }
        lastNodePosition -= 1;
        lastNode = openElementsStack.at(lastNodePosition);
    }
}
