/*! \class HTMLElement
 *
 * \brief Base HTMLElement class.
 */

#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>
#include <unordered_map>

class HTMLElement
{
    public:
        void addAttributesToElement(std::unordered_map<std::string,
                std::string> attributes);
        std::unordered_map<std::string, std::string> 
            getAttributesFromElement();
        std::string getElementName();
    protected:
        std::unordered_map<std::string, std::string> elementAttributes;
        std::string elementName;
};

#endif
