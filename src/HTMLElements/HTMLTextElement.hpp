#ifndef HTMLTEXTELEMENT_H
#define HTMLTEXTELEMENT_H

#include "HTMLElement.hpp"

class HTMLTextElement : public HTMLElement
{
    public:
        HTMLTextElement();
        bool is_text_node() const;
        void add_char(const wchar_t &next_char);
        void add_char(const std::wstring &next_char);
        std::wstring get_text() const;

    protected:
        std::wstring text;
};

#endif
