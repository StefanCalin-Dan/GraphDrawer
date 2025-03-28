#ifndef EDGE_H
#define EDGE_H
#include "node.h"
#include <memory>
class Edge
{
public:
    Edge();
    Edge(std::shared_ptr<Node> f, std::shared_ptr<Node> s);
    std::shared_ptr<Node> getFirst();
    std::shared_ptr<Node> getSecond();
private:
    std::shared_ptr<Node> m_first,m_second;
};

#endif
