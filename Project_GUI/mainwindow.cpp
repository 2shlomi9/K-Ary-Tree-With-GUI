
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tree(new Tree<int>())
{
    ui->setupUi(this);

    // Construct the tree with 10 nodes
    Node<int>* root = new Node<int>(1);
    tree->addRoot(*root);

    Node<int>* n1 = new Node<int>(17);
    Node<int>* n2 = new Node<int>(20);
    Node<int>* n3 = new Node<int>(5);
    Node<int>* n4 = new Node<int>(6);
    Node<int>* n5 = new Node<int>(30);
    Node<int>* n6 = new Node<int>(4);
    Node<int>* n7 = new Node<int>(7);
    Node<int>* n8 = new Node<int>(50);
    Node<int>* n9 = new Node<int>(10);
    Node<int>* n10 = new Node<int>(12);

    tree->addSubNode(*root, *n1);
    tree->addSubNode(*root, *n2);
    tree->addSubNode(*n1, *n3);
    tree->addSubNode(*n1, *n4);
    tree->addSubNode(*n2, *n5);
    tree->addSubNode(*n2, *n6);
    tree->addSubNode(*n3, *n7);
    tree->addSubNode(*n3, *n8);
    tree->addSubNode(*n7, *n9);
    tree->addSubNode(*n7, *n10);

    // Create a layout to hold the tree widgets
    layout = new QVBoxLayout;

    // Create the TreeWidget for visualization before heap transformation
    treeWidgetBefore = new TreeWidget(tree, this);
    treeWidgetBefore->setWindowTitle("Tree Before Transformation");
    layout->addWidget(treeWidgetBefore);


    // Construct copy of the tree
    Tree<int>* treeCopy = new Tree<int>;

    Node<int>* root1 = new Node<int>(1);

    treeCopy->addRoot(*root1);

    Node<int>* n11 = new Node<int>(17);
    Node<int>* n22 = new Node<int>(20);
    Node<int>* n33 = new Node<int>(5);
    Node<int>* n44 = new Node<int>(6);
    Node<int>* n55 = new Node<int>(30);
    Node<int>* n66 = new Node<int>(4);
    Node<int>* n77 = new Node<int>(7);
    Node<int>* n88 = new Node<int>(50);
    Node<int>* n99 = new Node<int>(10);
    Node<int>* n100 = new Node<int>(12);

    treeCopy->addSubNode(*root1, *n11);
    treeCopy->addSubNode(*root1, *n22);
    treeCopy->addSubNode(*n11, *n33);
    treeCopy->addSubNode(*n11, *n44);
    treeCopy->addSubNode(*n22, *n55);
    treeCopy->addSubNode(*n22, *n66);
    treeCopy->addSubNode(*n33, *n77);
    treeCopy->addSubNode(*n33, *n88);
    treeCopy->addSubNode(*n77, *n99);
    treeCopy->addSubNode(*n77, *n100);



    // Transform the tree into a minimum heap
    treeCopy->myHeap();

    // Create the TreeWidget for visualization after heap transformation
    treeWidgetAfter = new TreeWidget(treeCopy, this);
    treeWidgetAfter->setWindowTitle("Tree After Transformation");
    layout->addWidget(treeWidgetAfter);

    // Create a central widget and set the layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete treeWidgetBefore;
    delete treeWidgetAfter;
    delete tree;
}
