#ifndef TREEWIDGET_HPP
#define TREEWIDGET_HPP

#include <QWidget>
#include "../Sources/Tree.hpp"  

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    TreeWidget(Tree<int>* tree, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Tree<int>* tree;
    static const int nodeRadius = 20;
    static const int horizontalSpacing = 40;
    static const int verticalSpacing = 60;

    void drawTree(QPainter& painter, Node<int>* node, int x, int y, int level);
    int calculateSubtreeWidth(Node<int>* node);
};

#endif // TREEWIDGET_HPP