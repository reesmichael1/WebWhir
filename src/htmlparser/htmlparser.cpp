#include <boost/regex.hpp>

#include "htmlparser.h"

int get_wstring_iposition(std::wstring long_str, std::wstring substr);

// TODO: Check HTML requirements more strictly
bool HTMLParser::is_valid_html_string(std::wstring html_string)
{
    return HTMLParser::contains_doctype(html_string) &&
           HTMLParser::contains_root_element(html_string) &&
           HTMLParser::doctype_before_root(html_string);
}

bool HTMLParser::contains_doctype(std::wstring html_string)
{
    return (get_wstring_iposition(html_string, L"<!DOCTYPE") != -1);
}

bool HTMLParser::contains_root_element(std::wstring html_string)
{
    return HTMLParser::contains_root_open(html_string) &&
           HTMLParser::contains_root_close(html_string) &&
           HTMLParser::contains_root_open_before_close(html_string);
}

bool HTMLParser::contains_root_open(std::wstring html_string)
{
    boost::wregex html_root(L"<html\\s+.*>|<html>");
    boost::wsmatch results;
    return boost::regex_search(html_string, results, html_root);
}

bool HTMLParser::contains_root_close(std::wstring html_string)
{
    return (html_string.find(L"</html>") != std::wstring::npos);
}

bool HTMLParser::contains_root_open_before_close(std::wstring html_string)
{
    return (html_string.find(L"<html") < html_string.find(L"</html>"));
}

bool HTMLParser::doctype_before_root(std::wstring html_string)
{
    return get_wstring_iposition(html_string, L"<!DOCTYPE") <
        get_wstring_iposition(html_string, L"<html");
}
