#include "../HTMLElements/HTMLBodyElement.hpp"
#include "../HTMLElements/HTMLTextElement.hpp"

#include "HTMLParser.hpp"

#include <iostream>

HTMLParser::HTMLParser()
{
    tokenizer = HTMLTokenizer();
    head_element_pointer = nullptr;
    active_formatting_elements = {};
}

void HTMLParser::reconstruct_active_formatting_elements()
{
}

void HTMLParser::add_element_to_formatting_list(std::shared_ptr<HTMLElement> 
        element)
{
}

bool HTMLParser::is_element_in_scope(std::shared_ptr<HTMLElement> element)
{
    return true;
}

Document HTMLParser::construct_document_from_string(std::wstring html)
{
    Document document = Document();

    std::vector<std::unique_ptr<HTMLToken>> tokens = 
        tokenizer.tokenize_string(html);

    state = initial;

    std::shared_ptr<HTMLElement> current_node;

    for (std::vector<std::unique_ptr<HTMLToken>>::iterator it = tokens.begin(); 
            it != tokens.end(); it++)
    {
        const std::unique_ptr<HTMLToken> &token = *it;

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
                        open_elements.push(current_node);
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

                open_elements.push(html);
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
                    std::cout << "Before initializing head pointer" << std::endl;
                    // std::shared_ptr<HTMLHeadElement> head = 
                    //     std::make_shared<HTMLHeadElement>();
                    std::shared_ptr<HTMLHeadElement> head = 
                        construct_head_from_token(token);
                    std::cout << "Past initializing head pointer" << std::endl;
                    open_elements.push(head);
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
                    // std::shared_ptr<HTMLHeadElement> head = 
                    //     std::make_shared<HTMLHeadElement>();
                    std::shared_ptr<HTMLHeadElement> head = construct_head_element();
                    open_elements.push(head);
                    head_element_pointer = head;
                    it--;
                }

                state = in_head;
            }

            case in_head:
            {
                if (token->is_end_token() && token->get_tag_name() == L"head")
                {
                    open_elements.pop();
                    state = after_head;
                }

                // Many more states to implement

                break;
            }

            case after_head:
            {
                if (token->is_start_token() && 
                        token->get_tag_name() == L"body")
                {
                    std::shared_ptr<HTMLElement> body = 
                        construct_element_from_token(token);
                    open_elements.push(body);

                    state = in_body;
                }

                // Many more states to implement

                break;
            }

            case in_body:
            {
                if (token->is_char_token())
                {
                    std::shared_ptr<HTMLElement> char_node = 
                        construct_element_from_token(token);

                    reconstruct_active_formatting_elements();                    
                    open_elements.top()->add_text(char_node);
                }

                // Many more states to implement

                break;
            }

            case after_body:
            {
                break;
            }

            case after_after_body:
            {
                break;
            }


            default:
                break;
        }
    }

    return finalize_document(document);
}

Document HTMLParser::finalize_document(Document document)
{
    // https://www.w3.org/TR/2011/WD-html5-20110113/the-end.html#stop-parsing
    return document;
}

std::shared_ptr<HTMLElement> 
    HTMLParser::construct_element_from_token(const std::unique_ptr<HTMLToken> 
            &token)
{
    std::shared_ptr<HTMLElement> element = std::make_shared<HTMLElement>();
    return element;

    std::cout << "In construct_element_from_token" << std::endl;

    if (token->get_tag_name() == L"html")
        return element;

    else if (token->get_tag_name() == L"head")
    {
        std::cout << "Constructing head element" << std::endl;
        element = std::make_shared<HTMLHeadElement>();
        return element;
    }

    else if (token->get_tag_name() == L"body")
    {
        element = std::make_shared<HTMLBodyElement>();
        return element;
    }

    else if (token->is_char_token())
    {
        element = std::make_shared<HTMLTextElement>();
        return element;
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
    HTMLParser::construct_head_from_token(const std::unique_ptr<HTMLToken> 
            &head_token)
{
    std::shared_ptr<HTMLHeadElement> element = 
        std::make_shared<HTMLHeadElement>();

    return element;
}
