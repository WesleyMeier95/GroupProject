#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>

using namespace std;

class SplayTree;

class SplayNode{
public:
    SplayNode(int d, SplayNode *l = NULL, SplayNode *r = NULL):
        data(d), left(l), right(r) {}
    ~SplayNode() { delete left; delete right; }

    void printPreorder(ostream &os = cout, string indent = "") const;

    int data;
    SplayNode* left;
    SplayNode* right;
};

class SplayTree{
public:
    SplayTree() : root(NULL) {}
    virtual ~SplayTree() { delete root; }

    SplayNode* insertNode(int data, SplayNode* root);
    SplayNode* deleteNode(int data, SplayNode* root);
    SplayNode* search(int data, SplayNode* root)
        { return splay(data, root); }

    void printPreorder(ostream &os = cout) const
        { if (root) root->printPreorder(os); }

    SplayNode *root;

protected:

    SplayNode* LL_Rotate();
    SplayNode* RR_Rotate();


    SplayNode* splay(int data, SplayNode* root);
};

#endif // SPLAY_TREE_H
