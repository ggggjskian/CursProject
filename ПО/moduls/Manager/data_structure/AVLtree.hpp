#pragma once

#include <iostream>
#include "LinkedList.hpp" 

template<typename Key, typename dataType>
class AVLTree {
private:
    struct TreeNode {
        Key key;
        DoubleLinkedList<dataType> values;
        TreeNode* left;
        TreeNode* right;
        int balancefactor;

        TreeNode(const Key& k, dataType data) : key(k), balancefactor(0), left(nullptr), right(nullptr) {
            values.add(data);
        }
    };

    TreeNode* balanceL(TreeNode* p, bool& h) {
        TreeNode* p1;
        TreeNode* p2;
        if (p->balancefactor == -1) {
            p->balancefactor = 0;
        }
        else if (p->balancefactor == 0) {
            p->balancefactor = 1;
            h = false; 
        }
        else {
            p1 = p->right;
            if (p1->balancefactor >= 0) { // Одиночная RR
                p->right = p1->left;
                p1->left = p;
                if (p1->balancefactor == 0) {
                    p->balancefactor = 1;
                    p1->balancefactor = -1;
                    h = false; 
                }
                else {
                    p->balancefactor = 0;
                    p1->balancefactor = 0;
                }
                p = p1;
            }
            else { // двойная RL
                p2 = p1->left;
                p1->left = p2->right;
                p2->right = p1;
                p->right = p2->left;
                p2->left = p;
                if (p2->balancefactor == 1) p->balancefactor = -1;
                else p->balancefactor = 0;
                if (p2->balancefactor == -1) p1->balancefactor = 1;
                else p1->balancefactor = 0;
                p = p2;
                p2->balancefactor = 0;
            }
            h = false; 
        return p;
    }}

    TreeNode* balanceR(TreeNode* p, bool& h) {
        TreeNode* p1;
        TreeNode* p2;

        if (p->balancefactor == 1) {
            p->balancefactor = 0;
        }
        else if (p->balancefactor == 0) {
            p->balancefactor = -1;
            h = false; 
        }
        else {
            p1 = p->left;
            if (p1->balancefactor <= 0) { // одиночная LL
                p->left = p1->right;
                p1->right = p;
                if (p1->balancefactor == 0) {
                    p->balancefactor = -1;
                    p1->balancefactor = 1;
                    h = false; 
                }
                else {
                    p->balancefactor = 0;
                    p1->balancefactor = 0;
                }
                p = p1;
            }
            else { // двойная LR
                p2 = p1->right;
                p1->right = p2->left;
                p2->left = p1;
                p->left = p2->right;
                p2->right = p;
                if (p2->balancefactor == -1) {
                    p->balancefactor = 1;
                }
                else p->balancefactor = 0;
                if (p2->balancefactor == 1) {
                    p1->balancefactor = -1;
                }
                else p1->balancefactor = 0;
                p = p2;
                p2->balancefactor = 0;
            }
            h = false; 
        }
        return p;
    }

    TreeNode* findnode(TreeNode*& right, bool& h) {
        TreeNode* min;
        if (right->left != nullptr) {
            min = findnode(right->left, h);
            if (h == true) {
                right = balanceL(right, h);
            }
        }
        else {
            min = right;
            right = right->right;
            h = true; 
        }
        return min;
    }

    TreeNode* insert(TreeNode* p, const Key& key, dataType data, bool& h) {
        TreeNode* p1;
        TreeNode* p2;

        if (p == nullptr) {
            p = new TreeNode(key, data);
            h = true; 
        }
        else if (p->key > key) {
            p->left = insert(p->left, key, data, h);
            if (h) {
                switch (p->balancefactor) {
                case 0:
                    p->balancefactor = -1;
                    break;
                case 1:
                    p->balancefactor = 0;
                    h = false; 
                    break;
                case -1:
                    return balanceR(p, h);
                }
            }
        }
        else if (p->key < key) {
            p->right = insert(p->right, key, data, h);
            if (h) {
                switch (p->balancefactor) {
                case 0:
                    p->balancefactor = 1;
                    break;
                case -1:
                    p->balancefactor = 0;
                    h = false; 
                    break;
                case 1:
                    return balanceL(p, h);
                }
            }
        }
        else {
            p->values.add(data);
            h = false; 
        }
        return p;
    }

     TreeNode* remove(TreeNode* root, const Key& deletekey, bool& change_bf) {

        if (root == nullptr) {
            change_bf = false;
            return nullptr;
        }

        if (deletekey < root->key) {
            root->left = remove(root->left, deletekey, change_bf);
            if (change_bf) {
                root = balanceL(root, change_bf);
            }
        }
        else if (root->key < deletekey) {
            root->right = remove(root->right, deletekey, change_bf);
            if (change_bf) {
                root = balanceR(root, change_bf);
            }
        }
        else {
            TreeNode* left = root->left;
            TreeNode* right = root->right;
            delete root;
            if (left == nullptr) {
                change_bf = true; 
                return right;
            }
            if (right == nullptr) {
                change_bf = true; 
                return left;
            }

            TreeNode* min = findnode(right, change_bf);
            min->left = left;
            min->right = right;
            root = min;
            if (change_bf) {
                root = balanceL(root, change_bf);
            }
        }

        return root;
    }


    void printTree(TreeNode* node, int indent = 0) {
        if (node != nullptr) {
            printTree(node->right, indent + 4);

            for (int i = 0; i < indent; i++) {
                cout << " ";
            }

            cout << node->key << "(" << node->values.toSgtring() << ")" << endl;
            printTree(node->left, indent + 4);
        }
    }

    TreeNode* search(TreeNode* node, const Key& key) const {
        while (node != nullptr) {
            if (key < node->key) {
                node = node->left;
            }
            else if (node->key < key) {
                node = node->right;
            }
            else {
                return node;
            }
        }
        return nullptr;
    }

    void clear(TreeNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }




public: 

    TreeNode* root;

    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(const Key& key, dataType data) {
        bool h = false;
        root = insert(root, key, data, h); 
    }


    void remove(const Key& deletekey) {
        bool change_bf = false;
        root = remove(root, deletekey, change_bf);
    }


    TreeNode* search(const Key& key) const {
        return search(root, key);
    }



    void clearTree(){
        clear(root);
    }

    bool remove(const Key& key, const dataType& valueToRemove) {
        TreeNode* node = search(key);
        if (!node) {
            return false;
        }

        node->values.deleteNodeByValue(valueToRemove);

        if (node->values.isEmpty()) {
            this.remove(key);
        }

        return true;
    }



    void printTree() {
        printTree(root);
    }
};

