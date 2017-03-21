#ifndef HTMLTOKEN_H
#define HTMLTOKEN_H

#include <string>
#include <map>

class HTMLToken
{
    public:
        HTMLToken();
        std::wstring get_tag_name();
        bool is_self_closing();
        std::map<std::wstring, std::wstring> get_attributes();

    private:
        std::wstring tag_name;
        bool self_closing;
        std::map<std::wstring, std::wstring> attributes;
};

#endif
