#include "HTMLElement.hpp"

HTMLElement::HTMLElement()
{
    child_nodes = {};
    id = L"";
    title = L"";
}

HTMLElement::~HTMLElement()
{
}

HTMLElement::HTMLElement(const HTMLElement& element)
{
    child_nodes = element.child_nodes;
    id = element.id;
    title = element.title;
}

std::wstring HTMLElement::get_title()
{
    return title;
}

std::wstring HTMLElement::get_id()
{
    return id;
}

void HTMLElement::add_child(std::shared_ptr<HTMLElement> child_node)
{
    child_nodes.push_back(std::move(child_node));
}

std::vector<std::shared_ptr<HTMLElement>> HTMLElement::get_children()
{
    return child_nodes;
}

void HTMLElement::set_title(std::wstring element_title)
{
    title = element_title;
}

void HTMLElement::add_text(std::shared_ptr<HTMLElement> text_node)
{
    if (child_nodes.size() > 0 && child_nodes.back()->is_text_node())
        child_nodes.back()->add_char(text_node->get_text());
    else
        add_child(text_node);
}
