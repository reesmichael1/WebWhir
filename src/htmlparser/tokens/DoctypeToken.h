#ifndef DOCTYPETOKEN_H
#define DOCTYPETOKEN_H

#include <string>

class DoctypeToken
{
    public:
        DoctypeToken();
        DoctypeToken(wchar_t token_name);
        bool quirks_required();
        bool is_name_set();
        void set_is_name_set(bool is_set);
        bool is_public_identifier_set();
        bool is_system_identifier_set();
        std::wstring get_name();
        std::wstring get_public_identifier();
        std::wstring get_system_identifier();
        void set_quirks_required(bool required);
        void add_to_name(wchar_t char_to_add);

    private:
        bool require_quirks;
        bool name_set;
        bool public_identifier_set;
        bool system_identifier_set;
        std::wstring name;
        std::wstring public_identifier;
        std::wstring system_identifier;
};

#endif
