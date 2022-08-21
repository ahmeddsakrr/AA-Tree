#include <iostream>
#include "AA_Tree.h"
#include "AA_Tree.cpp" // must be included as templates were used

typedef int type;

void order(){
    cout << "\nPress 't' for new tree\n"
         << "Press 'i' to insert new value\n"
         << "Press 'd' to delete a value\n"
         << "Press 's' to search for a value\n"
         << "Press 'e' to check if the tree is empty\n"
         << "Press 'f' to find the n(th) value in the tree\n"
         << "Press 'l' to print level order of the tree\n"
         << "Press 'n' for inorder traversal of the tree\n"
         << "Press 'r' for preorder traversal of the tree\n"
         << "Press 'p' for postorder traversal of the tree\n"
         << "Press 'q' to quit\n"
         << "Choice:";
}

type getValue(){
    cout << "\nEnter value:";
    int value;
    cin >> value;
    return value;
}

int main() {
    auto *tree = new AA_Tree<type>;
    order();
    char choice;
    cin >> choice;
    while (choice != 'q') {
        switch (choice) {
            case 't':
                tree = new AA_Tree<type>;
                break;
            case 'i':
                tree->insert(getValue());
                break;
            case 'd':
                tree->remove(getValue());
                break;
            case 's':
                if(tree->search(getValue()))
                    cout << "Found\n";
                else
                    cout << "Not Found\n";
                break;
            case 'e':
                if(tree->empty()) cout << "Tree is empty\n";
                else cout << "Tree is not empty\n";
                break;
            case 'f':
                cout << "Enter the order of the element to find:";
                int elemOrder;
                cin >> elemOrder;
                cout << "The " << elemOrder << "th element is " << tree->findElement(elemOrder) << endl;
            case 'l':
                tree->print_level_order();
                break;
            case 'n':
                tree->print_in_order();
                break;
            case 'r':
                tree->preorderTraversal();
                break;
            case 'p':
                tree->postorderTraversal();
                break;
            default:
                cout << "Invalid order\n";
        }
        order();
        cin >> choice;
    }
}