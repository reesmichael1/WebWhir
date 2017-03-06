/*! \file 
 * \brief Impelment base HTMLElement class.
 *
 * \todo Many, many more element types to implement.
 */

#include <algorithm>

#include "htmlelement.h"

void HTMLElement::addAttributesToElement(std::unordered_map<std::string,
        std::string> attributes)
{
    for (auto attribute : attributes)
    {
        if (std::find(elementAttributes.begin(), elementAttributes.end(),
                    attribute) == elementAttributes.end())
        {
            elementAttributes.insert({attribute.first, attribute.second});
        }
    }
}

std::string HTMLElement::getElementName()
{
    return elementName;
}
