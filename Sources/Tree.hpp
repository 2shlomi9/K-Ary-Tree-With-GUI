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
        std::queue<Node<T>*> queue;
        Node<T>* current;
        bool isOnlyRoot;

    public:
        HeapIterator(Node<T>* ptr = nullptr) : current(ptr), isOnlyRoot(false){
            if (ptr != nullptr) {
                if(ptr->getNumOfChilds() == 0) {
                    isOnlyRoot = true;
                }
                else queue.push(ptr);
            }
        }

        T& operator*() const {
			return current->getValue();
		}

        T* operator->() const {
            return &(current->getValue());
        }

        HeapIterator& operator++() {
            if(isOnlyRoot){
                current = nullptr;
                return *this;
            }
            if(!queue.empty()){
                if(current == queue.front()){
                    queue.pop();
                    if(current->getChild(0))
                        queue.push(current->getChild(0));
                    if(current->getChild(1))
                        queue.push(current->getChild(1)); 
                    current = queue.front();
                    queue.pop();
                    if(current->getChild(0))
                        queue.push(current->getChild(0));
                    if(current->getChild(1))
                        queue.push(current->getChild(1)); 
                }
                else{
                    current = queue.front();
                    queue.pop();
                    if(current->getChild(0))
                        queue.push(current->getChild(0));
                    if(current->getChild(1))
                        queue.push(current->getChild(1)); 
                }
            }
            else current = nullptr;
            return *this;
        }
        bool operator==(const HeapIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const HeapIterator& other) const {
            return !(current == other.current);
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
        std::stack<Node<T>*> stack;
        Node<T>* current;
        bool isOnlyRoot;

    public:
        PreOrderIterator(Node<T>* ptr = nullptr) : current(ptr), isOnlyRoot(false){
            if (ptr != nullptr) {
                if(ptr->getNumOfChilds() == 0) {
                    isOnlyRoot = true;
                }
                else stack.push(ptr);
            }
            
        }

        T& operator*() const {
			return current->getValue();
		}

        T* operator->() const {
            return &(current->getValue());
        }

        PreOrderIterator& operator++() {
            if(isOnlyRoot){
                current = nullptr;
                return *this;
            }
        
            if (!stack.empty()) {
                if(current == stack.top()){ // in the first itaration current is equal to root and root is the top of the stack
                    stack.pop();
                    if(current->getChild(1))
                        stack.push(current->getChild(1));
                    if(current->getChild(0))
                        stack.push(current->getChild(0));
                    if(!stack.empty()){
                        current = stack.top();
                        stack.pop();
                    }
                    if(current->getChild(1))
                        stack.push(current->getChild(1));
                    if(current->getChild(0))
                        stack.push(current->getChild(0));                    
                }
                else{
                    current = stack.top();
                    stack.pop();
                    if(current->getChild(1))
                        stack.push(current->getChild(1));
                    if(current->getChild(0))
                        stack.push(current->getChild(0));        
                }
                    
            }
            else current = nullptr;
            return *this;
        }
        bool operator==(const PreOrderIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const PreOrderIterator& other) const {
            return !(current == other.current);
        }
    };
    
// -------------------- : PostOrderIterator Class : --------------------

    class PostOrderIterator {
    private:
        std::stack<Node<T>*> stack;
        std::stack<Node<T>*> tempStack;
        Node<T>* current;
        bool isOnlyRoot;

        void fillStack(){
            while(!tempStack.empty()){
                Node<T>* node = tempStack.top();
                tempStack.pop();
                stack.push(node);
                if(node->getChild(0))
                    tempStack.push(node->getChild(0));
                if(node->getChild(1))
                    tempStack.push(node->getChild(1));
            }

        }
        
        Node<T>* pushLeftChildren(Node<T>* node) {
            while (node->getChild(0)) {
                node = node->getChild(0);
            }
            return node;
        }


    public:
        PostOrderIterator(Node<T>* ptr = nullptr) : current(ptr), isOnlyRoot(false){
            if (ptr != nullptr) {
                if(ptr->getNumOfChilds() == 0) {
                    isOnlyRoot = true;
                }
                else{
                    tempStack.push(ptr);
                    fillStack();
                    current = pushLeftChildren(ptr);
                    stack.pop();
                }
            }
        }

        T& operator*() const {
			return current->getValue();
		}

        T* operator->() const {
            return &(current->getValue());
        }
        PostOrderIterator& operator++() {
            if(isOnlyRoot){
                current = nullptr;
                return *this;
            }
            if(!stack.empty()){
            current = stack.top();
            stack.pop();
            }
            else current = nullptr;
            return *this;
        }
        bool operator==(const PostOrderIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const PostOrderIterator& other) const {
            return !(current == other.current);
        }
    };


// -------------------- : InOrderIterator Class : --------------------

    class InOrderIterator {
    private:
        std::stack<Node<T>*> stack;
        Node<T>* current;
        bool isOnlyRoot;

        void fillStackByLeft(Node<T>* node){
            while(node){
                stack.push(node);
                node = node->getChild(0);
            }
        }
                
        Node<T>* pushLeftChildren(Node<T>* node) {
            while (node->getChild(0)) {
                node = node->getChild(0);
            }
            return node;
        }

    public:
        InOrderIterator(Node<T>* ptr = nullptr) : current(ptr), isOnlyRoot(false){
            if (ptr != nullptr) {
                if(ptr->getNumOfChilds() == 0) {
                    isOnlyRoot = true;
                }
                else{
                    fillStackByLeft(ptr);
                    current = pushLeftChildren(ptr);
                    stack.pop();
                }
            }
        }

        T& operator*() const {
			return current->getValue();
		}

        T* operator->() const {
            return &(current->getValue());
        }

        InOrderIterator& operator++() {
            if(isOnlyRoot){
                current = nullptr;
                return *this;
            }
            if(!stack.empty()){
                current = stack.top();
                stack.pop();
                if(current->getChild(1)){
                    fillStackByLeft(current->getChild(1));
                }
            }
            else current = nullptr;
            return *this;
        }

        bool operator==(const InOrderIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const InOrderIterator& other) const {
            return !(current == other.current);
        }
    };

// -------------------- : BFSIterator Class : --------------------
    class BFSIterator {
    private:
        std::queue<Node<T>*> queue;
        Node<T>* current;
        bool isOnlyRoot;

    public:
        BFSIterator(Node<T>* ptr = nullptr) : current(ptr), isOnlyRoot(false){
            if (ptr != nullptr) {
                if(ptr->getNumOfChilds() == 0) {
                    isOnlyRoot = true;
                }
                else queue.push(ptr);
            }
        }

        T& operator*() const {
			return current->getValue();
		}

        T* operator->() const {
            return &(current->getValue());
        }

        BFSIterator& operator++() {
            if(isOnlyRoot){
                current = nullptr;
                return *this;
            }
            if(!queue.empty()){
                if(current == queue.front()){
                    queue.pop();
                    for (size_t i = 0; i < current->getNumOfChilds(); ++i) {
                        if(current->getChild(i))
                            queue.push(current->getChild(i));
                    }
                    current = queue.front();
                    queue.pop();
                    for (size_t i = 0; i < current->getNumOfChilds(); ++i) {
                        if(current->getChild(i))
                            queue.push(current->getChild(i));
                    }
                }
                else{
                    current = queue.front();
                    queue.pop();
                    for (size_t i = 0; i < current->getNumOfChilds(); ++i) {
                        if(current->getChild(i))
                            queue.push(current->getChild(i));
                    }
                }
            }
            else current = nullptr;
            return *this;
        }
        bool operator==(const BFSIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const BFSIterator& other) const {
            return !(current == other.current);
        }
    };

// -------------------- : DFSIterator Class : --------------------

    class DFSIterator {
    private:
        std::stack<Node<T>*> stack;
        Node<T>* current;
        bool isOnlyRoot;

        void dfsFillStack(Node<T>* node){
            if(node){
                stack.push(node);
                for(size_t i=0; i<node->getNumOfChilds(); i++){
                    dfsFillStack(node->getChild(i));
                }
            }
        }

    public:
        DFSIterator(Node<T>* ptr = nullptr) : current(ptr), isOnlyRoot(false){
            if (ptr != nullptr) {
                if(ptr->getNumOfChilds() == 0) {
                    isOnlyRoot = true;
                }
                else{
                    dfsFillStack(ptr);
                    current = stack.top();
                    stack.pop();
                }
            }
        }

        T& operator*() const {
			return current->getValue();
		}

        T* operator->() const {
            return &(current->getValue());
        }

        DFSIterator& operator++() {
            if(isOnlyRoot){
                current = nullptr;
                return *this;
            }
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
            else current = nullptr;

            return *this;
        }
        bool operator==(const DFSIterator& other) const {
            return current == other.current;
        }
        bool operator!=(const DFSIterator& other) const {
            return !(current == other.current);
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
