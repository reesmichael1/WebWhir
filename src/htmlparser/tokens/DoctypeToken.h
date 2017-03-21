#ifndef DOCTYPETOKEN_H
#define DOCTYPETOKEN_H

class DoctypeToken
{
    public:
        DoctypeToken();
        bool quirks_required();
        bool is_name_set();
        bool is_public_identifier_set();
        bool is_system_identifier_set();

    private:
        bool require_quirks;
        bool name_set;
        bool public_identifier_set;
        bool system_identifier_set;
};

#endif
