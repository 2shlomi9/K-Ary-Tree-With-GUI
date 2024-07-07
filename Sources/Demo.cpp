#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"

using namespace std;

int main()
{
    Complex c1(1.0, 0.5);
    Complex c2(1.2, -0.3);
    Complex c3(1.9, 0.7);
    Complex c4(1.7, -0.6);
    Complex c5(1.8, 0.2);
    Complex c6(1.6, -0.4);
    Complex c7(1.4, 0.1);
    Complex c8(1.5, -0.1);
    Complex c9(1.1, 0.3);
    Complex c10(2.0, -0.2);

    Node<Complex> root_node (c1);
    Tree<Complex> tree; // Binary tree that contains Complex numbers.
    tree.addRoot(root_node);

    Node<Complex> n1 (c2);
    Node<Complex> n2 (c3);
    Node<Complex> n3 (c4);
    Node<Complex> n4 (c5);
    Node<Complex> n5 (c6);
    Node<Complex> n6 (c7);
    Node<Complex> n7 (c8);
    Node<Complex> n8 (c9);
    Node<Complex> n9 (c10);

    tree.addSubNode(root_node, n1);
    tree.addSubNode(root_node, n2);
    tree.addSubNode(n1, n3);
    tree.addSubNode(n1, n4);
    tree.addSubNode(n2, n5);
    tree.addSubNode(n2, n6);
    tree.addSubNode(n3, n7);
    tree.addSubNode(n3, n8);
    tree.addSubNode(n4, n9);

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << "Node Value: " << *node << endl;    
    } // prints the nodes in pre-order

    cout<<endl;

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << "Node Value: " << *node << endl; 
    } // prints the nodes in post-order

    cout<<endl;

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << "Node Value: " << *node << endl; 
    } // prints the nodes in in-order

    cout<<endl;

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << "Node Value: " << *node << endl; 
    } // prints the nodes in BFS order

    cout<<endl;
    
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << "Node Value: " << *node << endl; 
    } // prints the nodes in DFS order

    cout<<endl;
    // tree.myHeap();
    auto [heap_begin, heap_end] = tree.myHeap();
    
    for (auto node = heap_begin; node != heap_end; ++node)
    {
        cout << "Node Value: " << *node << endl; 
    } // prints the nodes in heap order

    cout << endl; 
    tree.cleanTree(); // clean tree for using the tree nodes again

    Tree<Complex,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.addRoot(root_node);
    three_ary_tree.addSubNode(root_node, n1);
    three_ary_tree.addSubNode(root_node, n2);
    three_ary_tree.addSubNode(root_node, n3);
    three_ary_tree.addSubNode(n1, n4);
    three_ary_tree.addSubNode(n2, n5);

    //  // The tree should look like:
    // /**
    //  *       root = 1.1+0.5i
    //  *     /      |     \
    //  * 1.2-0.3i 1.9+0.7i 1.7-0.6i
    //  *   /        |
    //  * 1.8+0.2i  1.6-0.4i
    //  */
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << "Node address: " << &node << ", Value: " << *node << endl; 
    } // prints the nodes in BFS order

    cout<<endl;
    
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node)
    {
        cout << "Node address: " << &node << ", Value: " << *node << endl; 
    } // prints the nodes in DFS order
}