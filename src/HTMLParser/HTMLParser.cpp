#include "HTMLParser.hpp"

HTMLParser::HTMLParser()
{
    tokenizer = HTMLTokenizer();
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
                    std::shared_ptr<HTMLHeadElement> head = 
                        std::make_shared<HTMLHeadElement>();
                    open_elements.push(head);
                    head_element_pointer = head;
                }

                break;
            }

            case in_head:
            case after_head:
            case in_body:
            case after_body:
            case after_after_body:

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
    HTMLParser::construct_element_from_token(const std::unique_ptr<HTMLToken> &token)
{
    std::shared_ptr<HTMLElement> element = std::make_shared<HTMLElement>();

    if (token->get_tag_name() == L"html")
        return element;

    else if (token->get_tag_name() == L"head")
    {
        element = std::make_shared<HTMLHeadElement>();
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
