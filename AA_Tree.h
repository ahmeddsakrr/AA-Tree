#ifndef PROJECT_AA_TREE_H
#define PROJECT_AA_TREE_H


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
    Node* root;
    Node* insert_node(T target,Node* node);
    Node* skew(Node* node);
    Node* split(Node* node);
    void level_order(Node* node);
    void in_order(Node* node);
    Node* right_rotation(Node* node);
    Node* left_rotation(Node* node);
public:
    AA_Tree();
    void insert(T value);
    void print_level_order();
    bool search(T target);
    void print_in_order();
};


#endif //PROJECT_AA_TREE_H
