#ifndef HTMLTOKEN_H
#define HTMLTOKEN_H

#include <string>
#include <map>

class HTMLToken
{
    public:
        // General HTMLToken properties
        virtual ~HTMLToken();
        std::wstring get_tag_name();
        void add_char_to_tag_name(wchar_t next_char);
        void set_name(std::wstring name);

        // Doctype Token functions
        virtual bool is_doctype_token() { return false; }
        virtual bool is_start_token() { return false; }
        virtual bool is_end_token() { return false; }
        virtual bool quirks_required() { return false; }
        virtual void set_quirks_required(bool required) {}
        virtual void set_is_name_set(bool is_set) {}
        virtual bool is_name_set() { return false; }
        virtual bool is_public_identifier_set() { return false; }
        virtual bool is_system_identifier_set() { return false; }
        virtual std::wstring get_public_identifier() { return NULL; }
        virtual std::wstring get_system_identifier() { return NULL; }

        // Start and End Token functions
        virtual bool is_self_closing() { return false; }
        virtual void set_self_closing(bool closing) {}
        virtual std::map<std::wstring, std::wstring> get_attributes() { return {}; }
        virtual void add_to_current_attribute_name(wchar_t next_char) {}
        virtual void add_to_current_attribute_value(wchar_t next_char) {}
        virtual std::wstring get_attribute_value(std::wstring attribute_name) { return NULL; }
        virtual bool contains_attribute(std::wstring attribute_name) { return false; }
        virtual void process_current_attribute() {}

        // Comment Token functions
        virtual bool is_comment_token() { return false; }
        virtual std::wstring get_data() { return NULL; }
        virtual void add_char_to_data(wchar_t next_char) {}
        virtual void set_data(std::wstring data_string) {}

    protected:
        std::wstring tag_name;
};

#endif
