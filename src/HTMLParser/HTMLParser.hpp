#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <string>
#include <stack>
#include <memory>

#include "HTMLTokenizer.hpp"
#include "tokens/HTMLToken.hpp"
#include "../HTMLElements/HTMLElement.hpp"
#include "../HTMLElements/HTMLHeadElement.hpp"
#include "../Document/Document.hpp"

class HTMLParser
{
    public:
        HTMLParser();
        Document construct_document_from_string(std::wstring html);
        std::shared_ptr<HTMLElement> 
            construct_element_from_token(const std::unique_ptr<HTMLToken> 
                    &token);

    protected:
        std::shared_ptr<HTMLElement> construct_html_element();
        std::shared_ptr<HTMLHeadElement> construct_head_element();
        std::shared_ptr<HTMLHeadElement> 
            construct_head_from_token(const std::unique_ptr<HTMLToken> 
                    &head_token);
        HTMLTokenizer tokenizer;
        std::stack<std::shared_ptr<HTMLElement>> open_elements;
        std::shared_ptr<HTMLHeadElement> head_element_pointer;
        Document finalize_document(Document document);
        void reconstruct_active_formatting_elements();
        void add_element_to_formatting_list(std::shared_ptr<HTMLElement> 
                element);
        std::list<std::shared_ptr<HTMLElement>> active_formatting_elements;
        bool is_element_in_scope(std::shared_ptr<HTMLElement> element);

        enum insertion_mode
        {
            initial,
            before_html,
            before_head,
            in_head,
            in_head_noscript,
            after_head,
            in_body,
            text,
            in_table,
            in_table_text,
            in_caption,
            in_column_group,
            in_table_body,
            in_row,
            in_cell,
            in_select,
            in_select_in_table,
            in_foreign_content,
            after_body,
            in_frameset,
            after_frameset,
            after_after_body,
            after_after_frameset
        };

        insertion_mode state;
};

#endif
