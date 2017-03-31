#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <list>
#include <memory>

#include "DocumentType.hpp"
#include "../HTMLElements/HTMLElement.hpp"

class Document
{
    public:
        Document();
        void add_element(std::shared_ptr<HTMLElement> element);
        std::list<std::shared_ptr<HTMLElement>> get_elements();
        DocumentType get_document_type();
        void set_quirks_mode(bool quirks);
        bool requires_quirks_mode();
        void set_document_type(std::wstring type);

    protected:
        std::list<std::shared_ptr<HTMLElement>> elements;
        DocumentType doc_type;
        bool quirks_mode;
};

#endif
