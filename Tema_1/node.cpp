#include "node.h"

Node::Node() {}

void Node::setValue(int val){m_value=val;}

void Node::setPos(QPoint p){m_pos=p;}

QPoint Node::getPos()const{return m_pos;}

int Node::getValue()const{return m_value;}

int Node::distance(QPoint pos){
    return (this->getPos().x() - pos.x())*(this->getPos().x() - pos.x()) + (this->getPos().y()- pos.y())*(this->getPos().y() - pos.y());
}

bool Node::operator==(const Node &node) const
{
    if(this->getPos().x() == node.getPos().x() &&this->getPos().y() == node.getPos().y() && this->getValue()==node.getValue())
        return true;
    else return false;
}
