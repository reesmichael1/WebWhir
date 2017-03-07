#ifndef __HTMLParser__
#define __HTMLParser__

#include <string>

class HTMLParser
{
    public:
        static bool is_valid_html_string(std::wstring html_string);

    private:
        static bool contains_doctype(std::wstring html_string);
        static bool contains_root_element(std::wstring html_string);
        static bool contains_root_open(std::wstring html_string);
        static bool contains_root_close(std::wstring html_string);
        static bool contains_root_open_before_close(std::wstring html_string);
        static bool doctype_before_root(std::wstring html_string);
};

#endif
