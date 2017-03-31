#ifndef DOCUMENTTYPE_H
#define DOCUMENTTYPE_H

#include <string>

class DocumentType
{
    public:
        DocumentType(std::wstring type_name);
        std::wstring get_name();
        void set_name(std::wstring type_name);

    protected:
        std::wstring name;
};

#endif
