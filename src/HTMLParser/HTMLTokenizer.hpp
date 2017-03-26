#ifndef HTMLTOKENIZER_H
#define HTMLTOKENIZER_H

#include <string>
#include <memory>

#include "tokens/HTMLToken.hpp"

class HTMLTokenizer
{
    public:
        static bool is_valid_html_string(std::wstring html_string);

        // A reasonably sized sublist of the possible parser states
        // (although most are not yet used)
        //
        // See www.w3.org/TR/2011/WD-html5-20110113/tokenization.html#data-state
        enum tokenizer_state
        {
            data_state,
            char_ref_in_data_state,
            rcdata_state,
            rawtext_state,
            plaintext_state,
            tag_open_state,
            end_tag_open_state,
            tag_name_state,
            rcdata_less_than_sign_state,
            rcdata_end_tag_name_state,
            rawtext_less_than_sign_state,
            rawtext_end_tag_name_state,
            before_attribute_name_state,
            attribute_name_state,
            after_attribute_name_state,
            before_attribute_value_state,
            attribute_value_double_quoted_state,
            attribute_value_single_quoted_state,
            attribute_value_unquoted_state,
            char_ref_in_attribute_value_state,
            after_attribute_value_quoted_state,
            self_closing_start_tag_state,
            bogus_comment_state,
            markup_declaration_open_state,
            comment_start_state,
            comment_start_dash_state,
            comment_state,
            comment_end_dash_state,
            comment_end_state,
            comment_end_bang_state,
            doctype_state,
            before_doctype_name_state,
            doctype_name_state,
            after_doctype_name_state,
            bogus_doctype_state,
            cdata_section_state
        };

        std::unique_ptr<HTMLToken> create_token_from_string(std::wstring 
                html_string, tokenizer_state &state);
        std::unique_ptr<HTMLToken> create_token_from_string(std::wstring 
                html_string);

    private:
        static bool contains_doctype(std::wstring html_string);
        static bool contains_root_element(std::wstring html_string);
        static bool contains_root_open(std::wstring html_string);
        static bool contains_root_close(std::wstring html_string);
        static bool contains_root_open_before_close(std::wstring html_string);
        static bool doctype_before_root(std::wstring html_string);

        tokenizer_state current_state;
};

#endif
