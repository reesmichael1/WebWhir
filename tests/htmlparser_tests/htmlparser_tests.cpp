#include <catch.hpp>

#include "../../src/htmlparser/htmlparser.h"

TEST_CASE("HTML validation tests")
{
    SECTION("Valid string")
    {
        std::wstring standard_html = L"<!DOCTYPE html><html></html>";
        CHECK(HTMLParser::is_valid_html_string(standard_html));

        std::wstring extra_spaces = L"<!DOCTYPE     html><html></html>";
        CHECK(HTMLParser::is_valid_html_string(extra_spaces));

        std::wstring front_and_back_spaces = 
            L"     <!DOCTYPE html><html></html>    ";
        CHECK(HTMLParser::is_valid_html_string(front_and_back_spaces));

        std::wstring middle_spaces = L"<!DOCTYPE html>   <html>   </html>";
        CHECK(HTMLParser::is_valid_html_string(middle_spaces));

        std::wstring doctype_case = L"<!DoCTyPE html><html></html>";
        CHECK(HTMLParser::is_valid_html_string(doctype_case));
        
        std::wstring lang_tag_in_root = 
            L"<!DOCTYPE html><html lang=\"en\"></html>";
        CHECK(HTMLParser::is_valid_html_string(lang_tag_in_root));
    }

    SECTION("Invalid string")
    {
        std::wstring no_doctype = L"<html></html>";
        CHECK_FALSE(HTMLParser::is_valid_html_string(no_doctype));

        std::wstring no_root = L"<!DOCTYPE html>";
        CHECK_FALSE(HTMLParser::is_valid_html_string(no_root));

        std::wstring root_not_closed = L"<!DOCTYPE html><html>";
        CHECK_FALSE(HTMLParser::is_valid_html_string(root_not_closed));

        std::wstring wrong_order = L"<html></html><!DOCTYPE html>";
        CHECK_FALSE(HTMLParser::is_valid_html_string(wrong_order));

        std::wstring root_wrong_order = L"</html><html><!DOCTYPE html>";
        CHECK_FALSE(HTMLParser::is_valid_html_string(root_wrong_order));

        std::wstring no_space_lang = 
            L"<!DOCTYPE html><htmllang=\"en\"></html>";
        CHECK_FALSE(HTMLParser::is_valid_html_string(no_space_lang));
    }
}
