#ifndef LOADER_H
#define LOADER_H

#include <string>

class Loader
{
    public:
        std::wstring load_from_file(std::string filename);
};

#endif
