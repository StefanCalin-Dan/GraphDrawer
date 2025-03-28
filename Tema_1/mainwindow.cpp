#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <cmath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_isFirstNodeSelected = false;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *m)
{
    if(m->button() == Qt::MiddleButton)
    {
        std::vector<std::shared_ptr<Node>>& nodes = m_graph.getNodes();
        std::vector<Edge>& edges = m_graph.getEdges();
        for(auto& n : nodes)
        {
            if((*n).distance(m->pos()) < 100)
            {
                m_isDraggingNode = true;
                m_draggedNode = n;
                m_dragOffset = m->pos() - (*n).getPos();
            }
        }
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *m)
{
    if(m_isDraggingNode && m->buttons() & Qt::MiddleButton)
    {
        if (m_draggedNode)
        {
            m_draggedNode->setPos(m->pos() - m_dragOffset);
            update();
        }
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    if(m->button() == Qt::RightButton)
    {
        if(m_graph.addNode(m->pos()))
        update();
    }
    else if(m->button() == Qt::MiddleButton)
    {
        if (m_isDraggingNode)
        {
            m_isDraggingNode = false;
            m_draggedNode = nullptr;
            update();
        }


    }
    else if(m->button() == Qt::LeftButton)
    {
        std::vector<std::shared_ptr<Node>>& nodes = m_graph.getNodes();
        for(auto& n:nodes)
        {
            if((*n).distance(m->pos()) < 100)

            {
                if(m_isFirstNodeSelected)
                {
                    m_graph.addEdge(m_selectedNode,n);
                    update();

                    m_isFirstNodeSelected = false;
                }
                else
                {
                    m_isFirstNodeSelected = true;
                    m_selectedNode = n;
                }
            }
        }

    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    std::vector<std::shared_ptr<Node>>& nodes = m_graph.getNodes();
    for(auto& n:nodes)
    {

        QBrush brush(Qt::white);
        p.setBrush(brush);

        QRect r((*n).getPos().x()-10,(*n).getPos().y()-10,20,20);
        p.drawEllipse(r);

        QPen pen;


        QFont font = p.font();
        font.setBold(true);
        p.setFont(font);

        pen.setColor(Qt::black);
        p.setPen(pen);
        p.drawText(r,Qt::AlignCenter,QString::number((*n).getValue()));
        pen.setColor(Qt::white);
        p.setPen(pen);


    }

    std::vector<Edge>& edges = m_graph.getEdges();
    for(auto& e:edges)
    {
        QPoint p1 = (*e.getFirst()).getPos();
        QPoint p2 = (*e.getSecond()).getPos();
        p.drawLine(p1,p2);

        if (m_graph.GetOrientedStatus())
        {

            double angle = std::atan2(p2.y() - p1.y(), p2.x() - p1.x());


            int arrowSize = 15;


            QPoint arrowP1((p1.x()+p2.x())/2,(p1.y()+p2.y())/2);

            QPoint arrowP2 = arrowP1 - QPoint(arrowSize * std::cos(angle - M_PI / 6),
                                         arrowSize * std::sin(angle - M_PI / 6));
            QPoint arrowP3 = arrowP1 - QPoint(arrowSize * std::cos(angle + M_PI / 6),
                                         arrowSize * std::sin(angle + M_PI / 6));


            QPolygon arrowHead;
            arrowHead << arrowP1 << arrowP2 << arrowP3;
            p.setBrush(Qt::red);
            p.drawPolygon(arrowHead);
        }
    }


}



void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(!m_graph.GetOrientedStatus())
        m_graph.SetOrientedStatus(true);
    else
        m_graph.SetOrientedStatus(false);
    update();
}




