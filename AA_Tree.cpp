#include <iostream>
#include <vector>
#include "AA_Tree.h"
using namespace std;

template<class T>
AA_Tree<T>::AA_Tree():root(nullptr) {}

template<class T>
AA_Tree<T>::~AA_Tree() {
    if(!empty()) destructorAux(root);
}

template<class T>
void destructorAux(typename AA_Tree<T>::NodePointer node){
    if(node->left) destructorAux(node->left);
    if(node->right) destructorAux(node->right);
    delete node;
}

template<class T>
bool AA_Tree<T>::empty() const{
    return !root;
}

template<class T>
typename AA_Tree<T>::NodePointer AA_Tree<T>::insert_node(T target, AA_Tree::NodePointer node) {
    if(!node)
        node= new Node(target);
    else if(target < node->value)
        node->left= insert_node(target,node->left);
    else if(target > node->value)
        node->right= insert_node(target,node->right);
    //else duplicate entry
    node= skew(node);
    return split(node);
}

template<class T>
typename AA_Tree<T>::NodePointer AA_Tree<T>::skew(AA_Tree::NodePointer node) {
    if (!node)
        return nullptr;
    if (node->left && node->level == node->left->level){
        // we perform right rotation to node
        return right_rotation(node);
    }
    else return node;
}

template<class T>
typename AA_Tree<T>::NodePointer AA_Tree<T>::split(AA_Tree::NodePointer node) {
    if (!node)
        return nullptr;
    if (node->right && node->right->right && node->level == node->right->right->level){
        //we perform left rotation to node
        return left_rotation(node);
    }else
        return node;
}

template<class T>
void AA_Tree<T>::insert(T value) {
    if(empty())
        root=new Node(value);
    else
        root= insert_node(value,root); // root can be changed.
}

template<class T>
void AA_Tree<T>::print_level_order() {
    if(empty()){
        cout<<"Error - Tree is empty\n";
        return;
    }
    vector<vector<T>> elements;
    level_order(root, elements);
    for(int i=1; i<=root->level; i++){
        cout << "Level " << i << ":";
        for(int j=0; j<elements[i].size(); j++){
            cout << " " << elements[i][j];
        }
        cout << endl;
    }
}

template<class T>
void AA_Tree<T>::level_order(AA_Tree::NodePointer node, vector<vector<T>> &elements) {
    if(node->left) level_order(node->left, elements);
    while (elements.size() <= node->level){
        vector<T> v;
        elements.push_back(v);
    }
    elements[node->level].push_back(node->value);
    if(node->right) level_order(node->right, elements);
}


template<class T>
typename AA_Tree<T>::NodePointer AA_Tree<T>::right_rotation(AA_Tree::NodePointer node) {
    NodePointer temp=node->left;
    node->left=temp->right;
    temp->right=node;
    return temp;
}

template<class T>
typename AA_Tree<T>::NodePointer AA_Tree<T>::left_rotation(AA_Tree::NodePointer node) {
    NodePointer temp=node->right;
    node->right=temp->left;
    temp->left=node;
    temp->level++;
    return temp;
}

template<class T>
bool AA_Tree<T>::search(T target) {
    NodePointer node=root;
    while(node){
        if (node->value == target)
            return true;
        if (target < node->value)
            node=node->left;
        else
            node=node->right;
    }
    return false;
}


template<class T>
void AA_Tree<T>::print_in_order() {
    if(!empty())
        in_order(root);
    else
        cout<<"Error - Tree is empty\n";
}

template<class T>
void AA_Tree<T>::in_order(AA_Tree::NodePointer node) {
    if (!node)
        return;
    in_order(node->left);
    cout<<node->value<<"(level"<<node->level<<") ";
    in_order(node->right);
}

template<class T>
void AA_Tree<T>::preorderTraversal(){
    if(!empty()) preorderTraversalAux(root);
    else cout<<"Error - Tree is empty\n";
}

template<class T>
void AA_Tree<T>::preorderTraversalAux(NodePointer node){
    if (!node) return;
    cout<<node->value<<"(level"<<node->level<<") ";
    preorderTraversalAux(node->left);
    preorderTraversalAux(node->right);
}

template<class T>
void AA_Tree<T>::postorderTraversal(){
    if(!empty()) postorderTraversalAux(root);
    else cout<<"Error - Tree is empty\n";
}

template<class T>
void AA_Tree<T>::postorderTraversalAux(NodePointer node){
    if (!node) return;
    postorderTraversalAux(node->left);
    postorderTraversalAux(node->right);
    cout<<node->value<<"(level"<<node->level<<") ";
}

template<class T>
void AA_Tree<T>::remove(const T &value){
    root = removeAux(value, root);
}

template<class T>
typename AA_Tree<T>::NodePointer AA_Tree<T>::removeAux(T value, NodePointer node){
    if(!node) return 0;

    if(value < node->value) node->left = removeAux(value, node->left);
    else if(value > node->value) node->right = removeAux(value, node->right);
    else{
        if(!node->left && !node->right) {
            delete node;
            return 0;
        }
        else{
            NodePointer successor = node->right;
            while(successor->left) successor = successor->left;
            node->value = successor->value;
            node->right = removeAux(node->value, node->right);
        }
    }

    //update level
    int newLevel;
    if(!node->left || !node->right) newLevel = 1;
    else newLevel = 1 + min(node->left->level, node->right->level);
    if(node->level>newLevel){
        node->level = newLevel;
        if(node->right && node->right->level>node->level)
            node->right->level = newLevel; // fix red child level
    }

    // worst case : 3 skews and 2 splits needed to maintain the tree
    node = skew(node);
    if(node->right) node->right = skew(node->right);
    if(node->right->right) node->right->right = skew(node->right->right);
    node = split(node);
    if(node->right) node->right = split(node->right);

    return node;
}

template<class T>
AA_Tree<T>::AA_Tree(const AA_Tree<T> &other)  {
    root=deep_copy(other.root);
}

template<class T>
typename AA_Tree<T>::Node *AA_Tree<T>::deep_copy(AA_Tree::Node *node) {
    if (node){
        Node* cur=new Node(node->value);
        cur->left= deep_copy(node->left);
        cur->right= deep_copy(node->right);
        return cur;
    }else
        return nullptr;
}

template<class T>
const AA_Tree<T> &AA_Tree<T>::operator=(const AA_Tree<T> &rightHandSide) {
    if(this == rightHandSide) return *this;
    this->~AA_Tree();
    if (rightHandSide.root){
        this->root= deep_copy(rightHandSide.root);
    }else
        root= nullptr;
    return *this;
}

template<class T>
T AA_Tree<T>::findElement(int & count){
    T value;
    bool found = false;
    findElementAux(count, root, found, value);
    if(found) return value;
    else{
        cerr << "No such element in the tree\n";
        exit(1);
    }
}

template<class T>
void findElementAux(int & count, typename AA_Tree<T>::NodePointer node, bool & found, T & value){
    if (!node || found) return;
    findElementAux(count, node->left, found, value);
    count--;
    if(!count){
        found = true;
        value = node->value;
        return;
    }
    findElementAux(count, node->right, found, value);
}