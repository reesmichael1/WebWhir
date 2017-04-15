#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>
#include <memory>

class HTMLElement
{
    public:
        HTMLElement();
        HTMLElement(const HTMLElement &element);
        virtual ~HTMLElement();
        std::wstring get_id() const;
        std::wstring get_title() const;
        void set_title(const std::wstring &element_title);
        void add_child(const std::shared_ptr<HTMLElement> child_node);
        std::vector<std::shared_ptr<HTMLElement>> get_children() const;
        void add_text(const std::shared_ptr<HTMLElement> text_node);
        
        // Text Node functions
        virtual bool is_text_node() const { return false; };
        virtual void add_char(const wchar_t &next_char) {};
        virtual void add_char(const std::wstring &next_char) {};
        virtual wchar_t get_char() const { return L'\0'; };
        virtual std::wstring get_text() const { return L""; };

        // Paragraph Node functions
        virtual bool is_paragraph_node() const { return false; };

    protected:
        std::wstring id;
        std::wstring title;
        std::vector<std::shared_ptr<HTMLElement>> child_nodes;
};

#endif
