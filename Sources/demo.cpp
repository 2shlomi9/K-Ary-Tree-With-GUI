#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"

using namespace std;



int main(){

    Tree<int> tree;
    Node<int> root(1);
    tree.addRoot(root);

    Node<int> n1(17);
    Node<int> n2(20);
    Node<int> n3(5);
    Node<int> n4(6);
    Node<int> n5(30);
    Node<int> n6(4);
    Node<int> n7(7);
    Node<int> n8(50);
    Node<int> n9(10);
    Node<int> n10(12);

    tree.addSubNode(root, n1);
    tree.addSubNode(root, n2);
    tree.addSubNode(n1, n3);
    tree.addSubNode(n1, n4);
    tree.addSubNode(n2, n5);
    tree.addSubNode(n2, n6);
    tree.addSubNode(n3, n7);
    tree.addSubNode(n3, n8);
    tree.addSubNode(n7, n9);
    tree.addSubNode(n7, n10);

    tree.printT();

}