#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include <vector>
#include <fstream>
#include <unordered_map>
class Graph
{
public:
    Graph();
    bool addNode(QPoint pos);
    bool addEdge(std::shared_ptr<Node> f, std::shared_ptr<Node> s);
    std::vector<std::shared_ptr<Node>>& getNodes();
    std::vector<Edge>& getEdges();
    std::vector<std::vector<bool>>& getAdjacencyMatrix();
    std::unordered_map<int,std::vector<int>>& getAdjacencyList();
    bool GetOrientedStatus();
    void SetOrientedStatus(bool status);
    void updateAdjacencyList();
    void updateAdjacencyMatrix();
private:
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::vector<Edge> m_edges;
    std::vector<std::vector<bool>>m_adjacencyMatrix;
    std::unordered_map<int,std::vector<int>> m_adjacencyList;

    bool m_isOriented;
};

#endif
