#include "graph.h"
#include <algorithm>
#include <fstream>

Graph::Graph() {m_isOriented = false;}

bool Graph::addNode(QPoint pos)
{
    for(auto& node:m_nodes)
    {
        if( (*node).distance(pos)< 400)
            return false;
    }
    Node n;
    n.setPos(pos);
    n.setValue(m_nodes.size()+1);
    m_nodes.push_back(std::make_shared<Node>(n));
    updateAdjacencyList();
    return true;

}

bool Graph::addEdge(std::shared_ptr<Node> f, std::shared_ptr<Node> s)
{

    if(f==s && m_isOriented==false)
        return false;
    for(auto& edge:m_edges)
    {
        if(edge.getFirst() == f && edge.getSecond()==s)
            return false;
    }
    Edge e(f,s);
    m_edges.push_back(e);
    updateAdjacencyList();
    return true;
}

std::vector<std::shared_ptr<Node>> &Graph::getNodes(){return m_nodes;}

std::vector<Edge> &Graph::getEdges(){return m_edges;}

std::vector<std::vector<bool> > &Graph::getAdjacencyMatrix()
{
    return m_adjacencyMatrix;
}

std::unordered_map<int,std::vector<int>>&Graph::getAdjacencyList()
{
    return m_adjacencyList;
}

bool Graph::GetOrientedStatus()
{
    return m_isOriented;
}

void Graph::SetOrientedStatus(bool status)
{
    m_isOriented = status;
    updateAdjacencyList();
}

void Graph::updateAdjacencyList()
{
    m_adjacencyList.clear();

    for (auto& node : m_nodes)
    {
        m_adjacencyList[(*node).getValue()] = {};
    }
    for (auto& edge : m_edges)
    {
        std::shared_ptr<Node> eFirst = edge.getFirst();
        std::shared_ptr<Node> eSecond = edge.getSecond();

        if (!m_isOriented && eFirst == eSecond)
        {
            continue;
        }

        if (std::find(m_adjacencyList[(*eFirst).getValue()].begin(),
                      m_adjacencyList[(*eFirst).getValue()].end(),
                      (*eSecond).getValue()) == m_adjacencyList[(*eFirst).getValue()].end())
        {
            m_adjacencyList[(*eFirst).getValue()].push_back((*eSecond).getValue());
        }


        if (!m_isOriented)
        {

            if (std::find(m_adjacencyList[(*eSecond).getValue()].begin(),
                          m_adjacencyList[(*eSecond).getValue()].end(),
                          (*eFirst).getValue()) == m_adjacencyList[(*eSecond).getValue()].end())
            {
                m_adjacencyList[(*eSecond).getValue()].push_back((*eFirst).getValue());
            }
        }
    }
    std::ofstream fout("../../AdjacencyList.txt");
    for(const auto& item:m_adjacencyList)
    {
        fout<<item.first<<": ";
        for(const auto& node:item.second)
            fout<<node<<", ";

        fout<<"\n";
    }
    fout.close();
    updateAdjacencyMatrix();

}

void Graph::updateAdjacencyMatrix()
{
    m_adjacencyMatrix.clear();
    std::vector<std::vector<bool>> temp(m_nodes.size()+1,std::vector<bool>(m_nodes.size()+1,false));
    m_adjacencyMatrix = temp;
    for(int i=0;i<m_adjacencyMatrix.size();i++)
    {
        for(int j=0;j<m_adjacencyMatrix[0].size();j++)
        {
            if(std::find(m_adjacencyList[i].begin(),m_adjacencyList[i].end(),j)!= m_adjacencyList[i].end())
            {
                m_adjacencyMatrix[i][j]=true;
                if(m_isOriented==false)
                    m_adjacencyMatrix[j][i]=true;
            }
        }
    }

    std::ofstream fout("../../AdjacencyMatrix.txt");
    fout<<m_adjacencyMatrix.size()-1<<"\n";
    for(int i=1;i<m_adjacencyMatrix.size();i++)
    {
        for(int j=1;j<m_adjacencyMatrix[0].size();j++)
        {
            if(m_adjacencyMatrix[i][j]==true)
                fout<<"1 ";
            else fout<<"0 ";
        }
        fout<<"\n";
    }
    fout.close();

}
