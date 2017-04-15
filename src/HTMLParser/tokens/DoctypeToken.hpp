#ifndef DOCTYPETOKEN_H
#define DOCTYPETOKEN_H

#include <string>

#include "HTMLToken.hpp"

class DoctypeToken : public HTMLToken
{
    public:
        DoctypeToken();
        DoctypeToken(wchar_t token_name);
        bool quirks_required() const;
        bool is_name_set() const;
        void set_is_name_set(bool is_set);
        bool is_public_identifier_set() const;
        bool is_system_identifier_set() const;
        std::wstring get_public_identifier() const;
        std::wstring get_system_identifier() const;
        void set_quirks_required(bool required);
        bool is_doctype_token() const;

    private:
        bool require_quirks;
        bool name_set;
        bool public_identifier_set;
        bool system_identifier_set;
        std::wstring public_identifier;
        std::wstring system_identifier;
};

#endif
