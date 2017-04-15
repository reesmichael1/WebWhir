#ifndef DOCUMENTTYPE_H
#define DOCUMENTTYPE_H

#include <string>

class DocumentType
{
    public:
        DocumentType(const std::wstring &type_name);
        std::wstring get_name() const;
        void set_name(const std::wstring &type_name);

    protected:
        std::wstring name;
};

#endif
