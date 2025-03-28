#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>


#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseReleaseEvent(QMouseEvent *m) override;
    void mousePressEvent(QMouseEvent *m) override;
    void mouseMoveEvent(QMouseEvent *m) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_checkBox_stateChanged(int arg1);



private:
    Ui::MainWindow *ui;
    Graph m_graph;
   std::shared_ptr<Node> m_selectedNode;
    std::shared_ptr<Node> m_draggedNode;
    bool m_isFirstNodeSelected;
    bool m_isDraggingNode;
    QPoint m_dragOffset;
};
#endif
