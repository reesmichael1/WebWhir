#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>

class HTMLElement
{
    public:
        HTMLElement();
        std::wstring get_id();
        std::wstring get_title();

    protected:
        std::wstring id;
        std::wstring title;
};

#endif
