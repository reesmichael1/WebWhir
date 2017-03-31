#include "HTMLElement.hpp"

HTMLElement::HTMLElement()
{
    child_nodes = {};
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
    child_nodes.push_back(child_node);
}

std::vector<std::shared_ptr<HTMLElement>> HTMLElement::get_children()
{
    return child_nodes;
}

void HTMLElement::set_title(std::wstring element_title)
{
    title = element_title;
}
