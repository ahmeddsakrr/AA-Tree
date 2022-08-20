#ifndef PROJECT_AA_TREE_H
#define PROJECT_AA_TREE_H
#include <vector>

using namespace std;

template<typename T>
class AA_Tree {

private:
    class Node{
    public:
        T value;
        short level;
        Node* right;
        Node* left;
        Node():level(0),right(nullptr),left(nullptr){}
        Node(T item):value(item),left(nullptr),right(nullptr),level(1){}
    };

    typedef Node* NodePointer;
    NodePointer root;

    NodePointer insert_node(T target,NodePointer node);
    NodePointer skew(NodePointer node);
    NodePointer split(NodePointer node);
    void level_order(NodePointer node, vector<vector<T>> &elements);
    void in_order(NodePointer node);
    void preorderTraversalAux(NodePointer node);
    void postorderTraversalAux(NodePointer node);
    NodePointer right_rotation(NodePointer node);
    NodePointer left_rotation(NodePointer node);
    NodePointer removeAux(T value, NodePointer node);
    Node* deep_copy(Node* node); // aux for copy constructor and assignment operator

public:
    AA_Tree();
    ~AA_Tree();
    void insert(T value);
    void print_level_order();
    bool search(T target);
    void print_in_order();
    void preorderTraversal();
    void postorderTraversal();
    void remove(const T &value);
    AA_Tree(const AA_Tree<T> &other);
    const AA_Tree<T> & operator= (const AA_Tree<T> & rightHandSide);
};


#endif //PROJECT_AA_TREE_H
