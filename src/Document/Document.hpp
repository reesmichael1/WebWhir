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
        void add_element(const std::shared_ptr<HTMLElement> element);
        std::list<std::shared_ptr<HTMLElement>> get_elements() const;
        DocumentType get_document_type() const;
        void set_quirks_mode(bool quirks);
        bool requires_quirks_mode();
        void set_document_type(const std::wstring &type);

    protected:
        std::list<std::shared_ptr<HTMLElement>> elements;
        DocumentType doc_type;
        bool quirks_mode;
};

#endif
