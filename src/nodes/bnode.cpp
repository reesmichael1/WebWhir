#include <iostream>
#include "bnode.h"

BNode::BNode()
{
    setNeedsPainting(true);
    setTypeOfNode("b");
}

void BNode::paintNode()
{
    std::cout << "The following text is bold:" << std::endl;
    std::cout << getText() << std::endl;
    std::cout << "The text is no longer bold." << std::endl;

}
