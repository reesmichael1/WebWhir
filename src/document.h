#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "rendernode.h"

class Document
{
public:
    Document();
    void constructTree(RenderNode *nodeToAdd);
    void addTagToVector(std::string tagToAdd);
    void removeTagFromVector(std::string tagToRemove, int position);

private:
    std::vector<std::string> vectorOfTags;

};

#endif // DOCUMENT_H
