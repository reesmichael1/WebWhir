#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>
#include <memory>

class HTMLElement
{
    public:
        HTMLElement();
        HTMLElement(const HTMLElement& element);
        virtual ~HTMLElement();
        std::wstring get_id();
        std::wstring get_title();
        void set_title(std::wstring element_title);
        void add_child(std::shared_ptr<HTMLElement> child_node);
        std::vector<std::shared_ptr<HTMLElement>> get_children();
        void add_text(std::shared_ptr<HTMLElement> text_node);
        
        // Text Node functions
        virtual bool is_text_node() { return false; }
        virtual void add_char(wchar_t next_char) {};
        virtual wchar_t get_char() { return L'\0'; };

    protected:
        std::wstring id;
        std::wstring title;
        std::vector<std::shared_ptr<HTMLElement>> child_nodes;
};

#endif
