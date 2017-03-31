#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>
#include <memory>

class HTMLElement
{
    public:
        HTMLElement();
        std::wstring get_id();
        std::wstring get_title();
        void set_title(std::wstring element_title);
        void add_child(std::shared_ptr<HTMLElement> child_node);
        std::vector<std::shared_ptr<HTMLElement>> get_children();

    protected:
        std::wstring id;
        std::wstring title;
        std::vector<std::shared_ptr<HTMLElement>> child_nodes;
};

#endif
