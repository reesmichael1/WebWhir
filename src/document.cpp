#include "rendernode.h"
#include "document.h"

Document::Document()
{
}

void Document::addTagToVector(std::string tagToAdd)
{
    vectorOfTags.push_back(tagToAdd);
}
