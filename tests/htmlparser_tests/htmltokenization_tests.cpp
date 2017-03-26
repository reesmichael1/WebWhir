#include <catch.hpp>
#include <map>
#include <string>

#include <boost/variant/get.hpp>

#include "../../src/htmlparser/htmlparser.h"
#include "../../src/htmlparser/tokens/StartToken.h"
#include "../../src/htmlparser/tokens/DoctypeToken.h"
#include "../../src/htmlparser/tokens/EndToken.h"

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
            StartToken html_token = StartToken();

            CHECK_FALSE(html_token.is_self_closing());
            CHECK(html_token.get_attributes() == empty_map);
            CHECK(html_token.get_tag_name() == L"");
        }
    }

    SECTION("Creating tokens with parser")
    {
        HTMLParser parser;

        SECTION("Creating doctype tokens with parser")
        {
            SECTION("Normal doctype token")
            {
                auto token = 
                    parser.create_token_from_string(L"<!DOCTYPE html>");
                DoctypeToken *doctype_token = 
                    dynamic_cast<DoctypeToken*>(token.get());

                REQUIRE(token->is_doctype_token());
                CHECK_FALSE(doctype_token->quirks_required());
                CHECK(doctype_token->is_name_set());
                CHECK(doctype_token->get_tag_name() == L"html");
            }

            SECTION("Doctype name not set")
            {
                // std::unique_ptr<HTMLToken> token = 
                auto token = 
                    parser.create_token_from_string(L"<!DOCTYPE>");
                DoctypeToken *doctype_token = 
                    dynamic_cast<DoctypeToken*>(token.get());

                REQUIRE(token->is_doctype_token());
                CHECK(doctype_token->quirks_required());
                CHECK_FALSE(doctype_token->is_name_set());
            }

            SECTION("Correctly handles extra identifiers")
            {
                std::wstring long_doctype = L"<!DOCTYPE HTML PUBLIC "  
                    L"\"-//W3C//DTD HTML 4.01 Transitional//EN\" "
                    L"\"http://www.w3.org/TR/html4/loose.dtd\">";
                std::unique_ptr<HTMLToken> token = 
                    parser.create_token_from_string(long_doctype);
                DoctypeToken *doctype_token = 
                    dynamic_cast<DoctypeToken*>(token.get());

                REQUIRE(token->is_doctype_token());
                CHECK(doctype_token->quirks_required());
                CHECK(doctype_token->get_tag_name() == L"html");
                CHECK(doctype_token->is_name_set());
            }
        }

        SECTION("Creating start tokens with parser")
        {
            std::map<std::wstring, std::wstring> lang_map = {{L"lang", L"en"}};

            SECTION("Creating html root token with parser")
            {
                // std::unique_ptr<HTMLToken> token = 
                auto token = 
                    parser.create_token_from_string(L"<HtMl lang=\"en\">");
                StartToken *start_token = 
                    dynamic_cast<StartToken*>(token.get());
                std::map<std::wstring, std::wstring> attributes_map = 
                    start_token->get_attributes();

                CHECK_FALSE(start_token->is_self_closing());
                CHECK(start_token->contains_attribute(L"lang"));
                CHECK(start_token->get_attribute_value(L"lang") == L"en");
                CHECK(start_token->get_tag_name() == L"html");
            }

            SECTION("Creating self-closing tag with parser")
            {
                std::unique_ptr<HTMLToken> token = 
                    parser.create_token_from_string(L"<br/>");
                StartToken *start_token = 
                    dynamic_cast<StartToken*>(token.get());

                CHECK(start_token->is_self_closing());
                CHECK(start_token->get_tag_name() == L"br");
            }

            SECTION("Tag with multiple attributes")
            {
                std::unique_ptr<HTMLToken> token = 
                    parser.create_token_from_string(
                        L"<img src=\"example.png\" width='10' height='20'>");
                StartToken *start_token = 
                    dynamic_cast<StartToken*>(token.get());
                std::map<std::wstring, std::wstring> attributes_map = 
                    start_token->get_attributes();

                CHECK(start_token->get_tag_name() == L"img");
                CHECK_FALSE(start_token->is_self_closing());
                CHECK(start_token->contains_attribute(L"src"));
                CHECK(start_token->contains_attribute(L"width"));
                CHECK(start_token->contains_attribute(L"height"));
                CHECK(start_token->get_attribute_value(L"src") == L"example.png");
                CHECK(start_token->get_attribute_value(L"width") == L"10");
                CHECK(start_token->get_attribute_value(L"height") == L"20");
            }

            SECTION("Tag with repeated attributes")
            {
                std::unique_ptr<HTMLToken> token = 
                    parser.create_token_from_string(
                                L"<html lang='en' lang='br'>");
                StartToken *start_token = 
                    dynamic_cast<StartToken*>(token.get());

                CHECK(start_token->get_tag_name() == L"html");
                CHECK(start_token->contains_attribute(L"lang"));
                CHECK(start_token->get_attribute_value(L"lang") == L"en");
                CHECK_FALSE(start_token->get_attribute_value(L"lang") == L"br");
                CHECK_FALSE(start_token->is_self_closing());
            }

            SECTION("Capitalization in attribute name/value")
            {
                std::unique_ptr<HTMLToken> token = 
                    parser.create_token_from_string(L"<html lAnG='eN'>");
                StartToken *start_token = 
                    dynamic_cast<StartToken*>(token.get());

                CHECK(start_token->get_tag_name() == L"html");
                CHECK(start_token->contains_attribute(L"lang"));
                CHECK(start_token->get_attribute_value(L"lang") == L"en");
                CHECK_FALSE(start_token->contains_attribute(L"lAnG"));
                CHECK_FALSE(start_token->is_self_closing());
            }

            SECTION("Self-closing tag with attributes")
            {
                std::unique_ptr<HTMLToken> token = 
                    parser.create_token_from_string(
                                L"<area shape=\"circle\"/>");
                StartToken *start_token = 
                    dynamic_cast<StartToken*>(token.get());

                CHECK(start_token->get_tag_name() == L"area");
                CHECK(start_token->is_self_closing());
                CHECK(start_token->contains_attribute(L"shape"));
                CHECK(start_token->get_attribute_value(L"shape") == L"circle");
            }
        }

        SECTION("Creating end tags with parser")
        {
            std::unique_ptr<HTMLToken> token = 
                parser.create_token_from_string(L"</p>");
            EndToken *end_token = 
                dynamic_cast<EndToken*>(token.get());

            CHECK(end_token->get_tag_name() == L"p");
            CHECK_FALSE(end_token->is_self_closing());
        }
    }
}
