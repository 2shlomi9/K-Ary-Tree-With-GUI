#ifndef NODE_HPP
#define NODE_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Node {
private:
    vector<Node*> children; // Using vector to manage child nodes
    T value; // Node value
    Node* parent; // Node parent
    size_t level;

public:
    // Constructors
    Node() : value(), parent(nullptr) {}
    Node(T new_value) : value(new_value), parent(nullptr) {}

    // Copy Constructor
    Node(const Node& other) : value(other.value), parent(nullptr) {
        for (auto child : other.children) {
            Node* new_child = new Node(*child); // Deep copy of each child
            addChild(new_child);
        }
    }

    // // Destructor
    // ~Node() {
    //     for (auto child : children) {
    //         delete child;
    //     }
    // }


    // Copy assignment operator
    Node& operator=(const Node& other) {
        if (this == &other) return *this;

        // Clear existing children
        for (auto child : children) {
            delete child;
        }
        children.clear();

        // Copy new data
        value = other.value;
        parent = nullptr; // Parent should not be copied
        for (auto child : other.children) {
            Node* new_child = new Node(*child); // Deep copy of each child
            addChild(new_child);
        }
        return *this;
    }

    // Return Node value
    T& getValue(){
        return this->value;
    }
    // Return Node value (const version)
    const T& getValue() const {
        return this->value;
    }

    // Set Node value
    void setValue(T val) {
        this->value = val;
    }

    void setLevel(size_t level){
        this->level = level;
    }

    size_t getLevel() const {
        return this->level;
    }

    // Return Node child by index 
    Node* getChild(size_t index) const {
        if (index < children.size()) {
            return children[index];
        }
        return nullptr;
    }

    // Return Node parent
    Node* getParent() const {
        return this->parent;
    }

    // Add child to the Node
    void addChild(Node* child) {
        children.push_back(child);
        child->parent = this;
    }

    size_t getNumOfChilds() const {
        return children.size();
    }

    Node* operator[](size_t index) const {
        return children[index];
    }

    void resetNodeData(){
        this->parent = nullptr;
        this->children.clear();
    }

    template<typename U>
    friend ostream& operator<<(ostream& os, const Node<U>& node);
};

template<typename U>
ostream& operator<<(ostream& os, const Node<U>& node) {
    os << "Node value = " << node.value << endl;
    os << "Number of children = " << node.children.size() << endl;
    if(node.getParent())
        os<< "Node parent = "<< node.getParent()->getValue()<<endl;
    return os;
}

#endif // NODE_HPP
