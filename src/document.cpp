#include "rendernode.h"
#include "document.h"

Document::Document()
{
}

std::vector<std::string> Document::getVectorOfTags()
{
    return vectorOfTags;
}

void Document::addTagToVector(std::string tagToAdd)
{
    vectorOfTags.push_back(tagToAdd);
}
