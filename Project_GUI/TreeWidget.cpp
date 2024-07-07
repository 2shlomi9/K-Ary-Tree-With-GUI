#include "TreeWidget.hpp"
#include <QPainter>
#include <QPen>
#include <algorithm>

TreeWidget::TreeWidget(Tree<int>* tree, QWidget *parent)
    : QWidget(parent), tree(tree)
{
}

void TreeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (tree && tree->getRoot()) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        drawTree(painter, tree->getRoot(), width() / 2, nodeRadius + 10, 0);
    }
}

int TreeWidget::calculateSubtreeWidth(Node<int>* node) {
    if (!node || node->getNumOfChilds() == 0) {
        return nodeRadius * 2;
    }

    int width = 0;
    for (size_t i = 0; i < node->getNumOfChilds(); ++i) {
        Node<int>* child = node->getChild(i);
        if (child) {
            width += calculateSubtreeWidth(child);
        }
    }

    width += (node->getNumOfChilds() - 1) * horizontalSpacing;
    return width;
}

void TreeWidget::drawTree(QPainter& painter, Node<int>* node, int x, int y, int level)
{
    if (!node) return;

    // Draw node circle
    painter.setBrush(Qt::yellow);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawEllipse(x - nodeRadius, y - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
    
    // Draw node value
    painter.drawText(x - 10, y + 5, QString::number(node->getValue()));

    // Draw edges to children
    size_t numOfChildren = node->getNumOfChilds();
    if (numOfChildren > 0) {
        int totalWidth = 0;
        for (size_t i = 0; i < numOfChildren; ++i) {
            Node<int>* child = node->getChild(i);
            if (child) {
                totalWidth += calculateSubtreeWidth(child);
            }
        }
        totalWidth += (numOfChildren - 1) * horizontalSpacing;

        int startX = x - totalWidth / 2;
        int childY = y + verticalSpacing;

        for (size_t i = 0; i < numOfChildren; ++i) {
            Node<int>* child = node->getChild(i);
            if (child) {
                int childWidth = calculateSubtreeWidth(child);
                int childX = startX + childWidth / 2;
                painter.drawLine(x, y + nodeRadius, childX, childY - nodeRadius);
                drawTree(painter, child, childX, childY, level + 1);
                startX += childWidth + horizontalSpacing;
            }
        }
    }
}
