#pragma once
#include <iostream>

struct Node {
    Node * left;
    Node * right;
    int value;
    int bf;
    int heightL;
    int heightR;
};

class Tree{
public:
    Tree();
    ~Tree();
    void insert(int);
    void del(int);
    int find(int);
    void print();

private:
    Node * root;
    bool balanced;
    void calculateBalanceFactor(Node *);
    void rebalance(Node *, Node *);
    int calculateHeight(Node *, int);
    void checkBalanceFactor(Node *, Node *);

    void rightRotation(Node *&, Node *);
    void leftRotation(Node *&, Node *);
    void rightLeftRotation(Node *&, Node *);
    void leftRightRotation(Node *&, Node *);
};