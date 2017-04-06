#include "Box.hpp"

Box::Box()
{
    width = -1;
    height = -1;
    coordinates = {-1, -1};
}

int Box::get_width()
{
    return width;
}

int Box::get_height()
{
    return height;
}

std::vector<int> Box::get_coordinates()
{
    return coordinates;
}

void Box::set_coordinates(std::vector<int> coords)
{
    coordinates = coords;
}

std::wstring Box::get_box_string()
{
    return string_in_box;
}

void Box::add_to_string(std::wstring string)
{
    string_in_box += string;
}

void Box::set_box_string(std::wstring string)
{
    string_in_box = string;
}

void Box::set_width(int new_width)
{
    width = new_width;
}

void Box::set_height(int new_height)
{
    height = new_height;
}
