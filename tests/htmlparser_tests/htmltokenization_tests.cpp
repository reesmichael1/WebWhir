#include <catch.hpp>
#include <map>
#include <string>

#include <boost/variant/get.hpp>

#include "../../src/HTMLParser/HTMLTokenizer.hpp"
#include "../../src/HTMLParser/tokens/StartToken.hpp"
#include "../../src/HTMLParser/tokens/DoctypeToken.hpp"
#include "../../src/HTMLParser/tokens/EndToken.hpp"
#include "../../src/HTMLParser/tokens/CommentToken.hpp"
#include "../../src/HTMLParser/tokens/CharacterToken.hpp"

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

    SECTION("Creating tokens with tokenizer")
    {
        HTMLTokenizer tokenizer;

        SECTION("Creating doctype tokens with tokenizer")
        {
            SECTION("Normal doctype token")
            {
                // auto doctype_string = L"<!DOCTYPE html>";
                auto doctype_string = L"<!DOCTYPE html>";
                auto doctype_token = 
                    tokenizer.create_token_from_string(doctype_string);

                REQUIRE(doctype_token->is_doctype_token());
                CHECK_FALSE(doctype_token->quirks_required());
                CHECK(doctype_token->is_name_set());
                CHECK(doctype_token->get_tag_name() == L"html");
            }

            SECTION("Doctype name not set")
            {
                auto doctype_token = 
                    tokenizer.create_token_from_string(L"<!DOCTYPE>");

                REQUIRE(doctype_token->is_doctype_token());
                CHECK(doctype_token->quirks_required());
                CHECK_FALSE(doctype_token->is_name_set());
            }

            SECTION("Correctly handles extra identifiers")
            {
                std::wstring long_doctype = L"<!DOCTYPE HTML PUBLIC "  
                    L"\"-//W3C//DTD HTML 4.01 Transitional//EN\" "
                    L"\"http://www.w3.org/TR/html4/loose.dtd\">";
                std::shared_ptr<HTMLToken> doctype_token = 
                    tokenizer.create_token_from_string(long_doctype);

                REQUIRE(doctype_token->is_doctype_token());
                CHECK(doctype_token->quirks_required());
                CHECK(doctype_token->get_tag_name() == L"html");
                CHECK(doctype_token->is_name_set());
            }
        }

        SECTION("Creating start tokens with tokenizer")
        {
            std::map<std::wstring, std::wstring> lang_map = {{L"lang", L"en"}};

            SECTION("Creating html root token with tokenizer")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(L"<HtMl lang=\"en\">");
                std::map<std::wstring, std::wstring> attributes_map = 
                    token->get_attributes();

                REQUIRE(token->is_start_token());
                CHECK_FALSE(token->is_self_closing());
                CHECK(token->contains_attribute(L"lang"));
                CHECK(token->get_attribute_value(L"lang") == L"en");
                CHECK(token->get_tag_name() == L"html");
            }

            SECTION("Creating self-closing tag with tokenizer")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(L"<br/>");

                REQUIRE(token->is_start_token());
                CHECK(token->is_self_closing());
                CHECK(token->get_tag_name() == L"br");
            }

            SECTION("Tag with multiple attributes")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(
                        L"<img src=\"example.png\" width='10' height='20'>");
                std::map<std::wstring, std::wstring> attributes_map = 
                    token->get_attributes();

                REQUIRE(token->is_start_token());
                CHECK(token->get_tag_name() == L"img");
                CHECK_FALSE(token->is_self_closing());
                CHECK(token->contains_attribute(L"src"));
                CHECK(token->contains_attribute(L"width"));
                CHECK(token->contains_attribute(L"height"));
                CHECK(token->get_attribute_value(L"src") == L"example.png");
                CHECK(token->get_attribute_value(L"width") == L"10");
                CHECK(token->get_attribute_value(L"height") == L"20");
            }

            SECTION("Tag with repeated attributes")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(
                                L"<html lang='en' lang='br'>");

                REQUIRE(token->is_start_token());
                CHECK(token->get_tag_name() == L"html");
                CHECK(token->contains_attribute(L"lang"));
                CHECK(token->get_attribute_value(L"lang") == L"en");
                CHECK_FALSE(token->get_attribute_value(L"lang") == L"br");
                CHECK_FALSE(token->is_self_closing());
            }

            SECTION("Capitalization in attribute name/value")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(L"<html lAnG='eN'>");

                REQUIRE(token->is_start_token());
                CHECK(token->get_tag_name() == L"html");
                CHECK(token->contains_attribute(L"lang"));
                CHECK(token->get_attribute_value(L"lang") == L"en");
                CHECK_FALSE(token->contains_attribute(L"lAnG"));
                CHECK_FALSE(token->is_self_closing());
            }

            SECTION("Self-closing tag with attributes")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(
                                L"<area shape=\"circle\"/>");

                REQUIRE(token->is_start_token());
                CHECK(token->get_tag_name() == L"area");
                CHECK(token->is_self_closing());
                CHECK(token->contains_attribute(L"shape"));
                CHECK(token->get_attribute_value(L"shape") == L"circle");
            }

            SECTION("Newline inside of tag")
            {
                auto token = 
                    tokenizer.create_token_from_string(L"<html\nlang=\"en\">");
                REQUIRE(token->is_start_token());
                CHECK(token->get_tag_name() == L"html");
                CHECK(token->contains_attribute(L"lang"));
                CHECK(token->get_attribute_value(L"lang") == L"en");
                CHECK_FALSE(token->is_self_closing());
            }
        }

        SECTION("Creating end tags with tokenizer")
        {
            std::shared_ptr<HTMLToken> token = 
                tokenizer.create_token_from_string(L"</p>");

            REQUIRE(token->is_end_token());
            CHECK(token->get_tag_name() == L"p");
            CHECK_FALSE(token->is_self_closing());

            SECTION("Newline inside of tag")
            {
                auto token = 
                    tokenizer.create_token_from_string(L"</p\n>");
                REQUIRE(token->is_end_token());
                CHECK(token->get_tag_name() == L"p");
                CHECK_FALSE(token->is_self_closing());
            }
        }

        SECTION("Creating character tokens with tokenizer")
        {
            std::shared_ptr<HTMLToken> token = 
                tokenizer.create_token_from_string(L"a");

            REQUIRE(token->is_char_token());
            CHECK(token->get_char() == L'a');
            CHECK_FALSE(token->is_self_closing());
        }

        SECTION("Creating comment tags with tokenizer")
        {
            SECTION("Normal comment")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(
                            L"<!--This is a comment-->");

                REQUIRE(token->is_comment_token());
                CHECK(token->get_data() == L"This is a comment");
            }

            SECTION("Normal comment with newline")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(
                            L"<!--This is\na comment-->");

                REQUIRE(token->is_comment_token());
                CHECK(token->get_data() == L"This is\na comment");
            }

            SECTION("Comment with no data")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(L"<!---->");

                REQUIRE(token->is_comment_token());
                CHECK(token->get_data() == L"");
            }

            SECTION("Comment with hyphen in data")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(L"<!--Test-string-->");

                REQUIRE(token->is_comment_token());
                CHECK(token->get_data() == L"Test-string");
            }

            SECTION("Comment with hyphen before data")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(L"<!---Test string-->");

                REQUIRE(token->is_comment_token());
                CHECK(token->get_data() == L"-Test string");
            }

            SECTION("Comment with two hyphens in the middle")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(L"<!--Test--string-->");

                REQUIRE(token->is_comment_token());
                CHECK(token->get_data() == L"Test--string");
            }

            SECTION("Comment with exclamation mark and hyphens in the middle")
            {
                std::shared_ptr<HTMLToken> token = 
                    tokenizer.create_token_from_string(
                            L"<!--Test--!string-->");

                REQUIRE(token->is_comment_token());
                CHECK(token->get_data() == L"Test--!string");
            }
        }
    }

    SECTION("Tokenizing multi-tag strings")
    {
        HTMLTokenizer tokenizer;

        SECTION("Well-formatted minimal string")
        {
            std::vector<std::shared_ptr<HTMLToken>> tokens = 
                tokenizer.tokenize_string(
                    L"<!DOCTYPE html><html><head></head><body></body></html>");

            REQUIRE(tokens.size() == 7);
            std::vector<std::shared_ptr<HTMLToken>>::iterator it = 
                tokens.begin();
            CHECK((*it)->is_doctype_token());
            CHECK((*it)->get_tag_name() == L"html");
            std::advance(it, 1);
            CHECK((*it)->is_start_token());
            CHECK((*it)->get_tag_name() == L"html");
            std::advance(it, 1);
            CHECK((*it)->is_start_token());
            CHECK((*it)->get_tag_name() == L"head");
            std::advance(it, 1);
            CHECK((*it)->get_tag_name() == L"head");
            CHECK((*it)->is_end_token());
            std::advance(it, 1);
            CHECK((*it)->is_start_token());
            CHECK((*it)->get_tag_name() == L"body");
            std::advance(it, 1);
            CHECK((*it)->get_tag_name() == L"body");
            CHECK((*it)->is_end_token());
            std::advance(it, 1);
            CHECK((*it)->get_tag_name() == L"html");
            CHECK((*it)->is_end_token());
        }


        SECTION("Well-formatted string with character tokens")
        {
            std::vector<std::shared_ptr<HTMLToken>> tokens = 
                tokenizer.tokenize_string(
                L"<!DOCTYPE html><html><head></head><body>Test</body></html>");

            REQUIRE(tokens.size() == 11);
            std::vector<std::shared_ptr<HTMLToken>>::iterator it = 
                tokens.begin();
            CHECK((*it)->is_doctype_token());
            CHECK((*it)->get_tag_name() == L"html");
            std::advance(it, 1);
            CHECK((*it)->is_start_token());
            CHECK((*it)->get_tag_name() == L"html");
            std::advance(it, 1);
            CHECK((*it)->is_start_token());
            CHECK((*it)->get_tag_name() == L"head");
            std::advance(it, 1);
            CHECK((*it)->get_tag_name() == L"head");
            CHECK((*it)->is_end_token());
            std::advance(it, 1);
            CHECK((*it)->is_start_token());
            CHECK((*it)->get_tag_name() == L"body");
            std::advance(it, 1);
            CHECK((*it)->get_char() == L'T');
            CHECK((*it)->is_char_token());
            std::advance(it, 1);
            CHECK((*it)->get_char() == L'e');
            CHECK((*it)->is_char_token());
            std::advance(it, 1);
            CHECK((*it)->get_char() == L's');
            CHECK((*it)->is_char_token());
            std::advance(it, 1);
            CHECK((*it)->get_char() == L't');
            CHECK((*it)->is_char_token());
            std::advance(it, 1);
            CHECK((*it)->get_tag_name() == L"body");
            CHECK((*it)->is_end_token());
            std::advance(it, 1);
            CHECK((*it)->get_tag_name() == L"html");
            CHECK((*it)->is_end_token());
        }
    }
}
