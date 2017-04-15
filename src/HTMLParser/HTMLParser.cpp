#include <iostream>

#include "../HTMLElements/HTMLBodyElement.hpp"
#include "../HTMLElements/HTMLTextElement.hpp"
#include "../HTMLElements/HTMLParagraphElement.hpp"
#include "HTMLParser.hpp"

HTMLParser::HTMLParser()
{
    tokenizer = HTMLTokenizer();
    head_element_pointer = nullptr;
    active_formatting_elements = {};
}

void HTMLParser::reconstruct_active_formatting_elements()
{
}

void HTMLParser::add_element_to_formatting_list(const 
        std::shared_ptr<HTMLElement> &element)
{
}

bool HTMLParser::is_element_in_scope(const std::wstring &element_title)
{
    return true;
}

void HTMLParser::insert_html_element(const std::shared_ptr<HTMLElement> &element)
{
    open_elements.back()->add_child(element);
    open_elements.push_back(element);
}

Document HTMLParser::construct_document_from_string(std::wstring &html)
{
    if (!tokenizer.is_valid_html_string(html))
        std::cerr << "ERROR: HTML string is not valid! "
            "Bad things may happen." << std::endl;
    Document document = Document();

    std::vector<std::shared_ptr<HTMLToken>> tokens = 
        tokenizer.tokenize_string(html);

    state = initial;

    std::shared_ptr<HTMLElement> current_node;

    for (std::vector<std::shared_ptr<HTMLToken>>::iterator it = tokens.begin(); 
            it != tokens.end(); it++)
    {
        const std::shared_ptr<HTMLToken> &token = *it;

        switch (state)
        {
            case initial:
            {
                if (token->is_doctype_token())
                {
                    document.set_document_type(token->get_tag_name());

                    // Other conditions (public/system identifiers)
                    if (token->quirks_required())
                        document.set_quirks_mode(true);

                    // More to do here
                    state = before_html; 
                }

                // space, comment: handle
                state = before_html; 
                break;
            }

            case before_html:
            {
                // DOCTYPE token: parse error
                // Comment, space: handle correctly
                
                if (token->is_start_token())
                {
                    if (token->get_tag_name() == L"html")
                    {
                        current_node = construct_element_from_token(token);
                        open_elements.push_back(current_node);
                        document.add_element(current_node);

                        state = before_head;

                        break;
                    }
                }

                // handle head, body, html, br end tokens
                
                else if (token->is_end_token() && 
                        !(token->get_tag_name() == L"head" ||
                            token->get_tag_name() == L"body" ||
                            token->get_tag_name() == L"html" ||
                            token->get_tag_name() == L"br"))
                    // parse error
                    break;


                std::shared_ptr<HTMLElement> html = construct_html_element();

                open_elements.push_back(html);
                document.add_element(html);

                current_node = construct_element_from_token(token);
                state = before_head;
                it--;

                break;
            }

            case before_head:
            {
                // Comment, space: handle correctly
                // HTML, Doctype: handle correctly
                if (token->is_start_token() && 
                        token->get_tag_name() == L"head")
                {
                    std::shared_ptr<HTMLHeadElement> head = 
                        construct_head_from_token(token);
                    open_elements.push_back(head);
                    head_element_pointer = head;
                }

                else if (token->is_end_token() && 
                        !(token->get_tag_name() == L"head" ||
                            token->get_tag_name() == L"body" ||
                            token->get_tag_name() == L"html" ||
                            token->get_tag_name() == L"br"))
                    break;

                else
                {
                    std::shared_ptr<HTMLHeadElement> head = construct_head_element();
                    open_elements.push_back(head);
                    head_element_pointer = head;
                    it--;
                }

                state = in_head;
            }

            case in_head:
            {
                if (token->is_end_token() && token->get_tag_name() == L"head")
                {
                    open_elements.pop_back();
                    state = after_head;
                }

                // Many more cases to implement

                break;
            }

            case after_head:
            {
                if (token->is_start_token() && 
                        token->get_tag_name() == L"body")
                {
                    std::shared_ptr<HTMLElement> body = 
                        construct_element_from_token(token);

                    insert_html_element(body);

                    state = in_body;
                }

                // Many more cases to implement

                break;
            }

            case in_body:
            {
                if (token->is_char_token())
                {
                    std::shared_ptr<HTMLElement> char_node = 
                        construct_element_from_token(token);

                    reconstruct_active_formatting_elements();
                    open_elements.back()->add_text(char_node);
                }

                else if (token->is_end_token())
                {
                    if (token->get_tag_name() == L"body")
                    {
                        // Other elements to check later
                        if (is_element_in_scope(L"body"))
                            state = after_body;    
                    }

                    else if (token->get_tag_name() == L"p")
                    {
                        // TODO
                        // Check if stack has element in button scope
                        // Generate implied end tags
                        // Check if current node is p node before popping
                        open_elements.pop_back();
                    }
                }
                
                else if (token->is_start_token())
                {
                    if (token->get_tag_name() == L"p")
                    {
                        // Other elements to check 
                        if (is_element_in_scope(L"p"))
                        {
                            current_node = construct_element_from_token(token);
                            insert_html_element(current_node);
                        }
                    }
                }

                // Many more cases to implement

                break;
            }

            case after_body:
            {
                if (token->is_end_token() && token->get_tag_name() == L"html")
                    state = after_after_body;

                // Many more cases to implement
                break;
            }

            case after_after_body:
            {
                // Many more cases to implement
                break;
            }


            default:
                break;
        }
    }

    return finalize_document(document);
}

Document HTMLParser::finalize_document(const Document &document)
{
    // https://www.w3.org/TR/2011/WD-html5-20110113/the-end.html#stop-parsing
    return document;
}

std::shared_ptr<HTMLElement> 
    HTMLParser::construct_element_from_token(const std::shared_ptr<HTMLToken> 
            &token)
{
    std::shared_ptr<HTMLElement> element = std::make_shared<HTMLElement>();

    if (token->get_tag_name() == L"html")
    {
        element->set_title(L"html");
        return element;
    }

    else if (token->get_tag_name() == L"head")
    {
        element = std::make_shared<HTMLHeadElement>();
        return element;
    }

    else if (token->get_tag_name() == L"body")
    {
        element = std::make_shared<HTMLBodyElement>();
        return element;
    }

    else if (token->get_tag_name() == L"p")
    {
        element = std::make_shared<HTMLParagraphElement>();
        return element;
    }

    else if (token->is_char_token())
    {
        std::shared_ptr<HTMLTextElement> text = 
            std::make_shared<HTMLTextElement>();
        text->add_char(token->get_char());

        return text;
    }

    else
        return element;
}

std::shared_ptr<HTMLElement> HTMLParser::construct_html_element()
{
    std::shared_ptr<HTMLElement> element = std::make_shared<HTMLElement>();
    element->set_title(L"html");

    return element;
}

std::shared_ptr<HTMLHeadElement> HTMLParser::construct_head_element()
{
    std::shared_ptr<HTMLHeadElement> element = 
        std::make_shared<HTMLHeadElement>();

    return element;
}

std::shared_ptr<HTMLHeadElement> 
    HTMLParser::construct_head_from_token(const std::shared_ptr<HTMLToken> 
            &head_token)
{
    std::shared_ptr<HTMLHeadElement> element = 
        std::make_shared<HTMLHeadElement>();

    return element;
}
