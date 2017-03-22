#include <catch.hpp>
#include <map>
#include <string>

#include "../../src/htmlparser/htmlparser.h"
#include "../../src/htmlparser/tokens/HTMLToken.h"
#include "../../src/htmlparser/tokens/DoctypeToken.h"

TEST_CASE("HTML tokenization")
{
    std::map<std::wstring, std::wstring> empty_map;
    SECTION("Manually creating tokens")
    {
        SECTION("Manually creating doctype token")
        {
            DoctypeToken doctype_token = DoctypeToken();
            CHECK_FALSE(doctype_token.quirks_required());
            CHECK_FALSE(doctype_token.is_name_set());
            CHECK_FALSE(doctype_token.is_public_identifier_set());
            CHECK_FALSE(doctype_token.is_system_identifier_set());
        }

        SECTION("Manually creating HTML root token")
        {
            HTMLToken html_token = HTMLToken();

            CHECK_FALSE(html_token.is_self_closing());
            CHECK(html_token.get_attributes() == empty_map);
            CHECK(html_token.get_tag_name() == L"");
        }
    }

    SECTION("Creating tokens with parser")
    {
        HTMLParser parser;
        std::map<std::wstring, std::wstring> lang_map = {{L"lang", L"en"}};

        SECTION("Creating html root token with parser")
        {
            HTMLToken token = 
                parser.create_token_from_string(L"<HtMl lang=\"en\">");
            std::map<std::wstring, std::wstring> attributes_map = 
                token.get_attributes();
            CHECK_FALSE(token.is_self_closing());
            CHECK(token.contains_attribute(L"lang"));
            CHECK(token.get_attribute_value(L"lang") == L"en");
            CHECK(token.get_tag_name() == L"html");
        }

        SECTION("Creating self-closing tag with parser")
        {
            HTMLToken token = parser.create_token_from_string(L"<br/>");
            CHECK(token.is_self_closing());
            CHECK(token.get_tag_name() == L"br");
        }

        SECTION("Tag with multiple attributes")
        {
            HTMLToken token = 
                parser.create_token_from_string(
                        L"<img src=\"example.png\" width='10' height='20'>");
            std::map<std::wstring, std::wstring> attributes_map = 
                token.get_attributes();
            CHECK_FALSE(token.is_self_closing());
            CHECK(token.contains_attribute(L"src"));
            CHECK(token.contains_attribute(L"width"));
            CHECK(token.contains_attribute(L"height"));
            CHECK(token.get_attribute_value(L"src") == L"example.png");
            CHECK(token.get_attribute_value(L"width") == L"10");
            CHECK(token.get_attribute_value(L"height") == L"20");
        }

        SECTION("Tag with repeated attributes")
        {
            HTMLToken token = 
                parser.create_token_from_string(L"<html lang='en' lang='br'>");
            CHECK(token.contains_attribute(L"lang"));
            CHECK(token.get_attribute_value(L"lang") == L"en");
            CHECK_FALSE(token.get_attribute_value(L"lang") == L"br");
            CHECK_FALSE(token.is_self_closing());
        }
    }
}
