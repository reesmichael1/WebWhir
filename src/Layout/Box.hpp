#ifndef BOX_H
#define BOX_H

#include <vector>
#include <string>

class Box
{
    public:
        Box();
        int get_width();
        int get_height();
        std::vector<int> get_coordinates();
        void set_coordinates(const std::vector<int> &coords);
        std::wstring get_box_string();
        void add_to_string(const std::wstring &string);
        void set_box_string(const std::wstring &string);
        void set_width(const int &new_width);
        void set_height(const int &new_height);
        void set_visible(bool v);
        bool is_visible();

    protected:
        int width;
        int height;
        std::vector<int> coordinates;
        std::wstring string_in_box;
        bool visible;
};

#endif
