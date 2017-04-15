#include "DocumentType.hpp"

DocumentType::DocumentType(const std::wstring &type_name)
{
    name = type_name;
}

std::wstring DocumentType::get_name() const
{
    return name;
}

void DocumentType::set_name(const std::wstring &type_name)
{
    name = type_name;
}
