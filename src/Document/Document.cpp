#include "Document.hpp"

Document::Document() : doc_type(L"")
{
    quirks_mode = false;
}

void Document::add_element(std::shared_ptr<HTMLElement> element)
{
    elements.push_back(element);
}

DocumentType Document::get_document_type()
{
    return doc_type;
}

std::list<std::shared_ptr<HTMLElement>> Document::get_elements()
{
    return elements;
}

void Document::set_quirks_mode(bool quirks)
{
    quirks_mode = quirks;
}

bool Document::requires_quirks_mode()
{
    return quirks_mode;
}

void Document::set_document_type(std::wstring type)
{
    doc_type.set_name(type);
}
