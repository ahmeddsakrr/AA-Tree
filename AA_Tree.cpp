#include <iostream>
#include <vector>
#include "AA_Tree.h"
using namespace std;

template<class T>
AA_Tree<T>::AA_Tree():root(nullptr) {}

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
    if(!root)
        root=new Node(value);
    else
        root= insert_node(value,root); // root can be changed.
}

template<class T>
void AA_Tree<T>::print_level_order() {
    if(root){
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
    else cout<<"Error - Tree is empty\n";
}

template<class T>
void AA_Tree<T>::level_order(AA_Tree::NodePointer node, vector<vector<T>> &elements) {
    if(node->left) level_order(node->left, elements);
    while (node->level >= elements.size()){
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
    if(root)
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