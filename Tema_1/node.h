#ifndef NODE_H
#define NODE_H
#include <QPoint>

class Node
{
public:
    Node();
    void setValue(int val);
    void setPos(QPoint p);
    QPoint getPos()const;
    int getValue()const;
    int distance(QPoint pos);
    bool operator==(const Node& node) const;
private:
    QPoint m_pos;
    int m_value;

};

#endif
