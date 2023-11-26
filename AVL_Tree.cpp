#include<iostream>

using namespace std;

class Node {
    public:
    int key, height;
    Node *left;
    Node *right;
};

class AVLTree{
    Node *root;
};