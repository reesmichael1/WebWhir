#ifndef STARTTOKEN_H
#define STARTTOKEN_H

#include <string>
#include <map>

#include "HTMLToken.hpp"

class StartToken : public HTMLToken
{
    public:
        StartToken();
        StartToken(wchar_t token_name);
        bool is_self_closing();
        void set_self_closing(bool closing);
        std::map<std::wstring, std::wstring> get_attributes();
        void add_to_current_attribute_name(wchar_t next_char);
        void add_to_current_attribute_value(wchar_t next_char);
        std::wstring get_attribute_value(std::wstring attribute_name);
        bool contains_attribute(std::wstring attribute_name);
        void process_current_attribute();
        bool is_start_token();

    private:
        bool self_closing;
        std::map<std::wstring, std::wstring> attributes;
        std::wstring current_attribute_name;
        std::wstring current_attribute_value;
};

#endif
