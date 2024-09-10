#ifndef TREE_HPP
#define TREE_HPP
#include "Node.hpp"
#include <stack>
#include <queue>
#include <utility>

// ----------------- Tree Class ----------------

template<typename T, size_t k=2>
    class Tree {
    private:
        Node<T>* root; // the root of the tree
        size_t max_childs; // max children to each node
        bool is_minimum_binary_heap;

    public:
        // Default constructor
        Tree() : root(nullptr), max_childs(k), is_minimum_binary_heap(false) {}

        // ~Tree(){
        //     cleanTree(this->root);
        //     delete this;
        // }
        // void cleanTree(Node<T>* node){
        //     if(!node) return;
        //     for (size_t i = 0; i < node->getNumOfChilds(); i++)
        //     {
        //         if(node->getChild(i)){
        //             cleanTree(node->getChild(i));
        //         }
        //     }
        //     delete node;
            
        // }


        
        // Add sub Node
        void addSubNode(Node<T>& parent, Node<T>& child){
            if(parent.getNumOfChilds() == max_childs){
                try
                {
                    throw std::invalid_argument("Each node must contains " + to_string(max_childs) + " children !\n");
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                return;
            }
            child.setLevel(parent.getLevel() + 1);
            parent.addChild(&child);
        }
        // Add root Node
        void addRoot(Node<T>& root){
            if(root.getParent()){
                throw std::invalid_argument("root can't be with parents !\n");
                return;
            }
            this->root = &root;
            this->root->setLevel(0);
        }

        Node<T>* getRoot(){
            return this->root;
        }

        // clean all nodes data from the tree
        void cleanTreeHelper(Node<T>* node){
        if (!node) return;
            node->resetNodeData();
            for (size_t i = 0; i < node->getNumOfChilds(); ++i) {
                cleanTreeHelper(node->getChild(i));
            }
        }
        void cleanTree(){
            cleanTreeHelper(this->root);
        }


    // -------------------- : myHeap Helper function : --------------------
    void myHeapHelper(Node<T>* node, vector<Node<T>*>& nodes) {
        if (!node) return;
            nodes.push_back(node);
        for (size_t i = 0; i < node->getNumOfChilds(); ++i) {
            myHeapHelper(node->getChild(i), nodes);
        }
    }

    void heapifyDown(vector<Node<T>*>& nodes, size_t index) {
        size_t leftChild = 2 * index + 1;
        size_t rightChild = 2 * index + 2;
        size_t smallest = index;

        if (leftChild < nodes.size() && nodes[leftChild]->getValue() < nodes[smallest]->getValue()) {
            smallest = leftChild;
        }
        if (rightChild < nodes.size() && nodes[rightChild]->getValue() < nodes[smallest]->getValue()) {
            smallest = rightChild;
        }
        if (smallest != index) {
            swap(nodes[index], nodes[smallest]);
            heapifyDown(nodes, smallest);
        }
    }



// -------------------- : HeapIterator Class : --------------------

    class HeapIterator{
    private:
        std::queue<Node<T>*> nodes;

    public:
        HeapIterator(Node<T>* ptr = nullptr){
            if(ptr != nullptr) nodes.push(ptr);
        }

        T& operator*() const {
			return nodes.front()->getValue();
		}

        T* operator->() const {
            return &(nodes.front()->getValue());
        }

        HeapIterator& operator++() {
            if(!nodes.empty()) {
                Node<T>* current = nodes.front();
                nodes.pop();
                for (size_t i = 0; i < current->getNumOfChilds(); i++)
                {
                    nodes.push(current->getChild(i));
                }
                
            }
            return *this;
        }
        HeapIterator operator++(int) {
            HeapIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const HeapIterator& other) const {
            if(nodes.empty() && other.nodes.empty()) return true;
            if(nodes.empty() || other.nodes.empty()) return false;
            return nodes.front() == other.nodes.front();
        }
        bool operator!=(const HeapIterator& other) const {
            return !(*this == other);
        }
    };
// -------------------- : myHeap function : --------------------

    pair<HeapIterator, HeapIterator> myHeap() {
        if (this->max_childs > 2) {
            throw std::invalid_argument("This function only works for binary trees.\n");
        }
        this->is_minimum_binary_heap = true;


        vector<Node<T>*> nodes;
        myHeapHelper(this->root, nodes);


        // Start heapifying down from the last non-leaf node
        for (int i = nodes.size() / 2 - 1; i >= 0; --i) {
            heapifyDown(nodes, static_cast<size_t>(i));
        }
        
        for (size_t i = 0; i < nodes.size(); i++)
        {
            nodes[i]->resetNodeData();
        }

        // Reconstruct the binary tree
        this->root = nodes[0];
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (2 * i + 1 < nodes.size()) nodes[i]->addChild(nodes[2 * i + 1]);
            if (2 * i + 2 < nodes.size()) nodes[i]->addChild(nodes[2 * i + 2]);
        }

        return {begin_heap_iterator(), end_heap_iterator()};
    }


// -------------------- : PreOrderIterator Class : --------------------
    
    class PreOrderIterator {
    private:
       stack<Node<T>*> nodes;

    public:
        PreOrderIterator(Node<T>* ptr){
            if(ptr != nullptr) nodes.push(ptr);
        }

        T& operator*() const {
			return nodes.top()->getValue();
		}

        T* operator->() const {
            return &(nodes.top()->getValue());
        }

        PreOrderIterator& operator++() {
            if(!nodes.empty()){
                Node<T>* current = nodes.top();
                nodes.pop();
                if(current->getChild(1)) nodes.push(current->getChild(1));
                if(current->getChild(0)) nodes.push(current->getChild(0));
            }
            return *this;
        }
        bool operator==(const PreOrderIterator& other) const {
            if(this->nodes.empty() && other.nodes.empty()) return true;
            if(this->nodes.empty() || other.nodes.empty()) return false;
            return this->nodes.top() == other.nodes.top();
        }
        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }
    };
    
// -------------------- : PostOrderIterator Class : --------------------

    class PostOrderIterator {
    private:
        stack<Node<T>*> nodes;

        void fillStack(Node<T>* node){
            if(!node) return;
            	nodes.push(node);
            if(node->getChild(1)) fillStack(node->getChild(1));
            if(node->getChild(0)) fillStack(node->getChild(0));
        }

    public:
        PostOrderIterator(Node<T>* ptr) {
            if(ptr != nullptr) fillStack(ptr);
        }

        T& operator*() const {
			return nodes.top()->getValue();
		}

        T* operator->() const {
            return &(nodes.top()->getValue());
        }
        PostOrderIterator& operator++() {
            if(!nodes.empty()){
                nodes.pop();
            }
            return *this;
        }
        bool operator==(const PostOrderIterator& other) const {
            if(this->nodes.empty() && other.nodes.empty()) return true;
            if(this->nodes.empty() || other.nodes.empty()) return false;
            return this->nodes.top() == other.nodes.top();
        }
        bool operator!=(const PostOrderIterator& other) const {
            return !(*this == other);
        }
    };


// -------------------- : InOrderIterator Class : --------------------

    class InOrderIterator {
    private:
        stack<Node<T>*> nodes;
        void fillStack(Node<T>* node){
            if(!node) return;
            if(node->getChild(1)) fillStack(node->getChild(1));
            nodes.push(node);
            if(node->getChild(0)) fillStack(node->getChild(0));

        }        

    public:
        InOrderIterator(Node<T>* ptr){
            if(ptr != nullptr) fillStack(ptr);
        }

        T& operator*() const {
			return nodes.top()->getValue();
		}

        T* operator->() const {
            return &(nodes.top()->getValue());
        }

        InOrderIterator& operator++() {
            if(!nodes.empty()) nodes.pop();
            return *this;
        }

        InOrderIterator& operator++(int) {
            InOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const InOrderIterator& other) const {
            if(this->nodes.empty() && other.nodes.empty()) return true;
            if(this->nodes.empty() || other.nodes.empty()) return false;
            return this->nodes.top() == other.nodes.top();
        }
        bool operator!=(const InOrderIterator& other) const {
            return !(*this == other);
        }
    };

// -------------------- : BFSIterator Class : --------------------
    class BFSIterator {
    private:
        std::queue<Node<T>*> nodes;
    public:
        BFSIterator(Node<T>* ptr) {
           if(ptr != nullptr) nodes.push(ptr);
        }

        T& operator*() const {
			return nodes.front()->getValue();
		}

        T* operator->() const {
            return &(nodes.front()->getValue());
        }

        BFSIterator& operator++() {
            if(!nodes.empty()) {
                Node<T>* current = nodes.front();
                nodes.pop();
                for (size_t i = 0; i < current->getNumOfChilds(); i++)
                {
                    nodes.push(current->getChild(i));
                }
                
            }
            return *this;
        }
        BFSIterator operator++(int) {
            BFSIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const BFSIterator& other) const {
            if(nodes.empty() && other.nodes.empty()) return true;
            if(nodes.empty() || other.nodes.empty()) return false;
            return nodes.front() == other.nodes.front();
        }
        bool operator!=(const BFSIterator& other) const {
            return !(*this == other);
        }
    };

// -------------------- : DFSIterator Class : --------------------

    class DFSIterator {
    private:
        std::stack<Node<T>*> nodes;

        void fillStack(Node<T>* node){
            if(!node) return;
            	nodes.push(node);
            for(int i=node->getNumOfChilds()-1; i>=0; i--){
                fillStack(node->getChild(static_cast<size_t>(i)));
            }
        }

    public:
        DFSIterator(Node<T>* ptr = nullptr){
            if (ptr != nullptr) {
                fillStack(ptr);
            }
        }

        T& operator*() const {
			return nodes.top()->getValue();
		}

        T* operator->() const {
            return &(nodes.top()->getValue());
        }

        DFSIterator& operator++() {
            if (!nodes.empty()) {
                nodes.pop();
            }
            return *this;
        }
        bool operator==(const DFSIterator& other) const {
            if(nodes.empty() && other.nodes.empty()) return true;
            if(nodes.empty() || other.nodes.empty()) return false;
            return nodes.top() == other.nodes.top();
        }
        bool operator!=(const DFSIterator& other) const {
            return !(*this == other);
        }
    };

// -------------------- Iterators Begin & End --------------------

    // --------- PreOrderIterator Begin & End ---------
    PreOrderIterator begin_pre_order() {
        return PreOrderIterator{root};
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator{nullptr};
    }

    // --------- PostOrderIterator Begin & End ---------

    PostOrderIterator begin_post_order() {
        return PostOrderIterator{root};
    }
    PostOrderIterator end_post_order() {
        return PostOrderIterator{nullptr};
    }

    // --------- InOrderIterator Begin & End ---------

    InOrderIterator begin_in_order() {
        return InOrderIterator{root};
    }
    InOrderIterator end_in_order() {
        return InOrderIterator{nullptr};
    }

    // --------- BFSIterator Begin & End ---------

    BFSIterator begin_bfs_scan() const {
        return BFSIterator{root};
    }

    BFSIterator end_bfs_scan() const {
        return BFSIterator{nullptr};
    }

    // --------- DFSIterator Begin & End ---------

    DFSIterator begin_dfs_scan() const {
        return DFSIterator{root};
    }
    DFSIterator end_dfs_scan() const {
        return DFSIterator{nullptr};
    }

    // --------- HeapIterator Begin & End ---------
    HeapIterator begin_heap_iterator() const{
        return HeapIterator{root};
    }
    HeapIterator end_heap_iterator() const{
        return HeapIterator{nullptr};
    }

    //-------------------------------------------------------------------
	// generic constructor:
	// template constructor inside a template class!
	//-------------------------------------------------------------------
	template<typename IT>
	Tree(IT begin_bfs_scan, IT end_bfs_scan): Tree() {
		for (; begin_bfs_scan!=end_bfs_scan; ++begin_bfs_scan) {
			push(*begin_bfs_scan);
		}
	}
	//-------------------------------------------------------------------

};






#endif // TREE_HPP
