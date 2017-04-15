#ifndef HTMLTOKEN_H
#define HTMLTOKEN_H

#include <string>
#include <map>

class HTMLToken
{
    public:
        // General HTMLToken properties
        virtual ~HTMLToken();
        std::wstring get_tag_name() const;
        void add_char_to_tag_name(wchar_t next_char);
        void set_tag_name(std::wstring name);

        // Doctype Token functions
        virtual bool is_doctype_token() const { return false; }
        virtual bool is_start_token() const { return false; }
        virtual bool is_end_token() const { return false; }
        virtual bool quirks_required() const { return false; }
        virtual void set_quirks_required(bool required) {}
        virtual void set_is_name_set(bool is_set) {}
        virtual bool is_name_set() const { return false; }
        virtual bool is_public_identifier_set() const { return false; }
        virtual bool is_system_identifier_set() const { return false; }
        virtual std::wstring get_public_identifier() const { return NULL; }
        virtual std::wstring get_system_identifier() const { return NULL; }

        // Start and End Token functions
        virtual bool is_self_closing() const { return false; }
        virtual void set_self_closing(bool closing) {}
        virtual std::map<std::wstring, std::wstring> get_attributes() const 
            { return {}; }
        virtual void add_to_current_attribute_name(wchar_t next_char) {}
        virtual void add_to_current_attribute_value(wchar_t next_char) {}
        virtual std::wstring get_attribute_value(std::wstring attribute_name) 
            const { return NULL; }
        virtual bool contains_attribute(std::wstring attribute_name) const
            { return false; }
        virtual void process_current_attribute() {}

        // Comment Token functions
        virtual bool is_comment_token() const { return false; }
        virtual std::wstring get_data() const { return NULL; }
        virtual void add_char_to_data(wchar_t next_char) {}
        virtual void set_data(std::wstring data_string) {}

        // Character Token functions
        virtual bool is_char_token() const { return false; }
        virtual wchar_t get_char() const { return L'\0'; };
        virtual void set_char(const wchar_t &char_to_set) {}

    protected:
        std::wstring tag_name;
};

#endif
