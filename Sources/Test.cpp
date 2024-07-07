/*
Author : Shlomi Zecharia
ID : 315141242
Email : 2shlomiariel9@gmail.com
*/

#include "doctest.h"
#include "Tree.hpp"
#include "Node.hpp"
#include "Complex.hpp"
#include <sstream> 

using namespace std;

TEST_CASE("Complex Operators") {
    Complex a(1.0, 2.0);
    Complex b(3.0, 4.0);

    SUBCASE("Unary Operators") {
        CHECK(!Complex(0, 0));
        CHECK(!(Complex(1, 1) == !Complex(1, 1)));

        Complex c = -a;
        CHECK(c.re() == -1.0);
        CHECK(c.im() == -2.0);
    }

    SUBCASE("Binary Operators") {
        Complex c = a + b;
        CHECK(c.re() == 4.0);
        CHECK(c.im() == 6.0);

        c = a - b;
        CHECK(c.re() == -2.0);
        CHECK(c.im() == -2.0);

        a += b;
        CHECK(a.re() == 4.0);
        CHECK(a.im() == 6.0);

        a -= b;
        CHECK(a.re() == 1.0);
        CHECK(a.im() == 2.0);

        a *= b;
        CHECK(a.re() == -5.0);
        CHECK(a.im() == 10.0);
    }

    SUBCASE("Comparison Operators") {
        Complex c(1.0005, 2.0);

        CHECK(a == a);
        CHECK(a != b);
        CHECK(a < b);
        CHECK(b > a);
        CHECK(a <= c);
        CHECK(a >= c);
    }

    SUBCASE("Increment Operators") {
        Complex c = a;

        ++a;
        CHECK(a.re() == 2.0);
        CHECK(a.im() == 2.0);

        a++;
        CHECK(a.re() == 3.0);
        CHECK(a.im() == 2.0);

        CHECK(c.re() == 1.0);
        CHECK(c.im() == 2.0);
    }

    SUBCASE("Ostream Operator") {
        ostringstream oss;
        oss << a;
        CHECK(oss.str() == "1+2i");
    }
}

/*
Author : Shlomi Zecharia
ID : 315141242
Email : 2shlomiariel9@gmail.com
*/

#include "doctest.h"
#include "Node.hpp"

using namespace std;

TEST_CASE("Node Class Tests") {
    SUBCASE("Default Constructor") {
        Node<int> node;
        CHECK(node.getValue() == 0); // Default constructed value for int
        CHECK(node.getParent() == nullptr);
        CHECK(node.getNumOfChilds() == 0);
    }

    SUBCASE("Parameterized Constructor") {
        Node<int> node(5);
        CHECK(node.getValue() == 5);
        CHECK(node.getParent() == nullptr);
        CHECK(node.getNumOfChilds() == 0);
    }

    SUBCASE("Copy Constructor") {
        Node<int> parent(5);
        Node<int>* child1 = new Node<int>(10);
        Node<int>* child2 = new Node<int>(15);
        parent.addChild(child1);
        parent.addChild(child2);

        Node<int> copiedParent = parent;
        CHECK(copiedParent.getValue() == 5);
        CHECK(copiedParent.getNumOfChilds() == 2);
        CHECK(copiedParent.getChild(0)->getValue() == 10);
        CHECK(copiedParent.getChild(1)->getValue() == 15);

        // Ensure deep copy
        child1->setValue(100);
        CHECK(copiedParent.getChild(0)->getValue() == 10);
    }

    SUBCASE("Assignment Operator") {
        Node<int> parent(5);
        Node<int>* child1 = new Node<int>(10);
        Node<int>* child2 = new Node<int>(15);
        parent.addChild(child1);
        parent.addChild(child2);

        Node<int> assignedNode;
        assignedNode = parent;
        CHECK(assignedNode.getValue() == 5);
        CHECK(assignedNode.getNumOfChilds() == 2);
        CHECK(assignedNode.getChild(0)->getValue() == 10);
        CHECK(assignedNode.getChild(1)->getValue() == 15);

        // Ensure deep copy
        child1->setValue(100);
        CHECK(assignedNode.getChild(0)->getValue() == 10);
    }

    SUBCASE("Value Accessors and Mutators") {
        Node<int> node(5);
        CHECK(node.getValue() == 5);

        node.setValue(10);
        CHECK(node.getValue() == 10);
    }

    SUBCASE("Child Management") {
        Node<int> parent(5);
        Node<int>* child1 = new Node<int>(10);
        Node<int>* child2 = new Node<int>(15);
        parent.addChild(child1);
        parent.addChild(child2);

        CHECK(parent.getNumOfChilds() == 2);
        CHECK(parent.getChild(0)->getValue() == 10);
        CHECK(parent.getChild(1)->getValue() == 15);

        CHECK(child1->getParent() == &parent);
        CHECK(child2->getParent() == &parent);
    }

    SUBCASE("Operator[]") {
        Node<int> parent(5);
        Node<int>* child1 = new Node<int>(10);
        Node<int>* child2 = new Node<int>(15);
        parent.addChild(child1);
        parent.addChild(child2);

        CHECK(parent[0]->getValue() == 10);
        CHECK(parent[1]->getValue() == 15);
    }

    SUBCASE("Reset Node Data") {
        Node<int> node(5);
        Node<int>* child = new Node<int>(10);
        node.addChild(child);

        node.resetNodeData();
        CHECK(node.getParent() == nullptr);
        CHECK(node.getNumOfChilds() == 0);
    }

}



TEST_CASE("Tree Class Tests") {
    Tree<int> tree;
    
    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);

    tree.addRoot(root);
    tree.addSubNode(root, child1);
    tree.addSubNode(root, child2);
    tree.addSubNode(child1, child3);
    tree.addSubNode(child1, child4);

    SUBCASE("PreOrder Iterator") {
        vector<int> expected = {1, 2, 4, 5, 3};
        size_t i = 0; 

        for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }
    }

    SUBCASE("PostOrder Iterator") {
        vector<int> expected = {4, 5, 2, 3, 1};
        size_t i = 0; 

        for (auto it = tree.begin_post_order(); it != tree.end_post_order(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }

    }

    SUBCASE("InOrder Iterator") {
        vector<int> expected = {4, 2, 5, 1, 3};
        size_t i = 0; 

        for (auto it = tree.begin_in_order(); it != tree.end_in_order(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }

    }

    SUBCASE("BFS Iterator") {
        vector<int> expected = {1, 2, 3, 4, 5, 6};
        size_t i = 0; 

        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }

    }

    SUBCASE("DFS Iterator") {
        vector<int> expected = {3, 5, 4, 2, 1};
        size_t i = 0; 

        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }

    }

    SUBCASE("Heap Iterator") {
        tree.myHeap();

        vector<int> expected = {1, 2, 4, 5, 3};
        size_t i = 0; 

        for (auto it = tree.begin_heap_iterator(); it != tree.end_heap_iterator(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }
    }
}
TEST_CASE("4-Ary Tree Class Tests") {
    Tree<int, 4> tree;

    Node<int> root(1);
    Node<int> child1(2);
    Node<int> child2(3);
    Node<int> child3(4);
    Node<int> child4(5);
    Node<int> child5(6);
    Node<int> child6(7);
    Node<int> child7(8);
    Node<int> child8(9);
    Node<int> child9(10);
    Node<int> child10(11);
    Node<int> child11(12);
    Node<int> child12(13);
    Node<int> child13(14);
    Node<int> child14(15);
    Node<int> child15(16);
    Node<int> child16(17);

    tree.addRoot(root);
    tree.addSubNode(root, child1);
    tree.addSubNode(root, child2);
    tree.addSubNode(root, child3);
    tree.addSubNode(root, child4);
    
    tree.addSubNode(child1, child5);
    tree.addSubNode(child1, child6);
    tree.addSubNode(child1, child7);
    tree.addSubNode(child1, child8);
    
    tree.addSubNode(child2, child9);
    tree.addSubNode(child2, child10);
    tree.addSubNode(child2, child11);
    tree.addSubNode(child2, child12);
    
    tree.addSubNode(child3, child13);
    tree.addSubNode(child3, child14);
    tree.addSubNode(child3, child15);
    tree.addSubNode(child3, child16);

    SUBCASE("BFS Iterator") {
        vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
        size_t i = 0;

        for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }
    }

    SUBCASE("DFS Iterator") {
        vector<int> expected = {5, 17, 16, 15, 14, 4, 13, 12, 11, 10, 3, 9, 8, 7, 6, 2, 1};
        size_t i = 0;

        for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
            CHECK(expected[i] == *it);
            i++;
        }
    }
}