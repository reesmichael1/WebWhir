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

        SECTION("Creating doctype token with parser")
        {
            HTMLToken token = parser.create_token_from_string(L"<!DOCTYPE html>");
        }
    }
}
