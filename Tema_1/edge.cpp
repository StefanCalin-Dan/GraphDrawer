#include "edge.h"



Edge::Edge(std::shared_ptr<Node> f, std::shared_ptr<Node> s):m_first{f},m_second{s}{}

std::shared_ptr<Node> Edge::getFirst(){return m_first;}

std::shared_ptr<Node> Edge::getSecond(){return m_second;}
