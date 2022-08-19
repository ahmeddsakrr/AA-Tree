#include <iostream>
#include "AA_Tree.h"
#include "AA_Tree.cpp" // must be included as templates were used
int main() {
    AA_Tree<int> tree;
    tree.insert(1);
    tree.print_level_order();
    cout<<endl;
    tree.insert(5);
    tree.print_level_order();
    cout<<endl;
    tree.insert(10);
    tree.print_level_order();
    cout<<endl;
    tree.insert(2);
    tree.print_level_order();
    cout<<endl;
    tree.insert(6);
    tree.print_level_order();
    cout<<endl;
    tree.insert(98);
    tree.print_level_order();
    cout<<endl;

    cout<<"Printing InOrder: \n";
    tree.print_in_order();
    cout<<endl<<endl;

    cout<<"Preorder Traversal: \n";
    tree.preorderTraversal();
    cout<<endl<<endl;

    cout<<"Postorder Traversal: \n";
    tree.postorderTraversal();
    cout<<endl<<endl;

    cout<<boolalpha;
    cout<<tree.search(10)<<endl;
    cout<<tree.search(100)<<endl;
    cout<<endl<<endl;

    tree.remove(5);
    tree.print_level_order();
    return 0;
}
