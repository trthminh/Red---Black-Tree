#ifndef RBTREE_H
#define RBTREE_H
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

struct node
{
    int val;
    char color;
    node *left, *right, *parent;
};

class RBTree
{
    public:
        RBTree();
        virtual ~RBTree();
        void InsertNode(int);
        void InsertFix(node *);
        void findX(int );
        void DeleteNode(node *);
        void DeleteFix(node *);
        void LeftRotate(node *);
        void RightRotate(node *);
        void disp();
        void _display_tree(node *root);
        void SearchNode(int);
        int getNumberNode();
        node* successor(node*);
        void fixDoubleBlack(node*);
        node* BSTreplace(node *x);
        node* sibling(node *);

    protected:

    private:
        node *root;
        int numberOfNode;
};

#endif // RBTREE_H
