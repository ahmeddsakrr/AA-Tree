#include <iostream>
#include <string>
#include "AA_Tree.h"
#include "AA_Tree.cpp" // must be included as templates were used

void order(int type){
    if(type==1){
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
    else{
        cout << "\nPress 'i' for a tree of integers\n"
             << "Press 'f' for a tree of floats\n"
             << "Press 'd' for a tree of doubles\n"
             << "Press 's' for a tree of strings\n"
             << "Press 'c' for a tree of chars\n"
             << "Press 'q' to quit\n"
             << "Choice:";
    }
}

void clear(AA_Tree<int>* &iTree, AA_Tree<float>* &fTree, AA_Tree<double>* &dTree,
           AA_Tree<string>* &sTree, AA_Tree<char>* &cTree){
    /*******************************************************
     The design choice was to clear all trees content each
     time a new tree is requested for memory saving.
     *******************************************************/
    iTree = new AA_Tree<int>;
    fTree = new AA_Tree<float>;
    dTree = new AA_Tree<double>;
    sTree = new AA_Tree<string>;
    cTree = new AA_Tree<char>;
}

template<typename type>
void program(AA_Tree<type>* tree){
    type value;
    order(1);
    char choice;
    cin >> choice;
    while (true) {
        switch (choice) {
            case 't':
                return;
            case 'i':
                cout << "\nEnter value:";
                cin >> value;
                tree->insert(value);
                break;
            case 'd':
                cout << "\nEnter value:";
                cin >> value;
                tree->remove(value);
                break;
            case 's':
                cout << "\nEnter value:";
                cin >> value;
                if(tree->search(value))
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
                value = tree->findElement(elemOrder);
                switch (elemOrder%10) { //for correct grammar
                    case 1:
                        cout << "The " << elemOrder << "st element is " << value << endl;
                        break;
                    case 2:
                        cout << "The " << elemOrder << "nd element is " << value << endl;
                        break;
                    case 3:
                        cout << "The " << elemOrder << "rd element is " << value << endl;
                        break;
                    default:
                        cout << "The " << elemOrder << "th element is " << value << endl;
                }
                break;
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
            case 'q':
                exit(0);
            default:
                cout << "Invalid order\n";
        }
        order(1);
        cin >> choice;
    }
}

int main() {
    auto *iTree = new AA_Tree<int>;
    auto *fTree = new AA_Tree<float>;
    auto *dTree = new AA_Tree<double>;
    auto *sTree = new AA_Tree<string>;
    auto *cTree = new AA_Tree<char>;

    order(2);
    char choice;
    cin >> choice;
    while(true){
        switch(choice){
            case 'i':
                clear(iTree, fTree, dTree, sTree, cTree);
                program(iTree);
                break;
            case 'f':
                clear(iTree, fTree, dTree, sTree, cTree);
                program(fTree);
                break;
            case 'd':
                clear(iTree, fTree, dTree, sTree, cTree);
                program(dTree);
                break;
            case 's':
                clear(iTree, fTree, dTree, sTree, cTree);
                program(sTree);
                break;
            case 'c':
                clear(iTree, fTree, dTree, sTree, cTree);
                program(cTree);
                break;
            case 'q':
                return 0;
            default:
                cout << "\nInvalid Choice\n";
        }
        order(2);
        cin >> choice;
    }
}