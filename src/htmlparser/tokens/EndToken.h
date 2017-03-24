#ifndef ENDTOKEN_H
#define ENDTOKEN_H

#include <string>
#include <map>

class EndToken
{
    public:
        EndToken();
        std::wstring get_tag_name();
        bool is_self_closing();
        void set_self_closing(bool closing);
        std::map<std::wstring, std::wstring> get_attributes();
        void set_name(std::wstring name);
        void add_to_current_attribute_name(wchar_t next_char);
        void add_to_current_attribute_value(wchar_t next_char);
        std::wstring get_attribute_value(std::wstring attribute_name);
        bool contains_attribute(std::wstring attribute_name);
        void process_current_attribute();

    private:
        std::wstring tag_name;
        bool self_closing;
};

#endif
