#include "DocumentType.hpp"

DocumentType::DocumentType(std::wstring type_name)
{
    name = type_name;
}

std::wstring DocumentType::get_name()
{
    return name;
}

void DocumentType::set_name(std::wstring type_name)
{
    name = type_name;
}
