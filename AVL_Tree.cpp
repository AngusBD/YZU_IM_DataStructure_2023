#include<iostream>
#include<cmath>

using namespace std;

class Node {
    friend class AVLTree;
public:
    int value;
    Node* left;
    Node* right;

    Node(): value(0), left(NULL), right(NULL){};

    Node(int v): value(v), left(NULL), right(NULL){};
};

class AVLTree{
public: 
    Node* root;
    AVLTree():root(NULL){};

    bool isTreeEmpty(){
        if(root == NULL){
            return true; 
        }
        return false;
    }

    int getNodeHeight(Node* node){
        if(node == NULL){
            return -1;
        }
        
        int lheight = getNodeHeight(node->left);
        int rheight = getNodeHeight(node->right);

        return max(lheight, rheight) + 1;
    }

    int getBalanceFactor(Node* node){
        if(node == NULL){
            return -1;
        }
        return getNodeHeight(node->left) - getNodeHeight(node->right);
    }

    Node* rightRotate(Node* node){
        Node* leftChild = node->left;
        Node* tempNode = leftChild->right;

        //Rotation
        leftChild->right = node;
        node->left = tempNode;

        return leftChild;
    }

    Node* leftRotate(Node* node){
        Node* rightChild = node->right;
        Node* tempNode = rightChild->left;

        //Rotation
        rightChild->left = node;
        node->right = tempNode;

        return rightChild;
    }

    Node* insert(Node* targetNode, Node* newNode){
        if(targetNode == NULL){
            targetNode = newNode;
            cout << "insertComplete!" << endl;
            return targetNode;
        }

        if(newNode->value < targetNode->value){
            targetNode->left = insert(targetNode->left, newNode);
        }
        else if(newNode->value > targetNode->value){
            targetNode->right = insert(targetNode->right, newNode);
        }
        else{
            cout << "insertError!" << endl;
            return targetNode;
        }

        int bf = getBalanceFactor(targetNode);
        // LL Case
        if(bf > 1 && newNode->value < targetNode->left->value){
            return rightRotate(targetNode);
        }

        //RR Case
        if(bf < -1 && newNode->value > targetNode->right->value){
            return leftRotate(targetNode);
        }

        //LR Case
        if(bf > 1 && newNode->value > targetNode->left->value){
            targetNode->left = leftRotate(targetNode->left);
            return rightRotate(targetNode);
        }

        //RL Case
        if(bf < -1 && newNode->value < targetNode->right->value){
            targetNode->right = rightRotate(targetNode->right);
            return leftRotate(targetNode);
        }

        return targetNode;
    }

    void print2D(Node* node, int space){
        if(node == NULL){
            return;
        }

        space += 10;
        print2D(node->right, space);
        cout << endl;
        for(int i = 10; i < space; i++){
            cout << " ";
        }
        cout << node->value << "\n";
        print2D(node->left, space);
    }
};

int main(){
    AVLTree obj;
    int testCase[6] = {55, 32, 22, 40, 27, 18};
    for(int i = 0; i < 6; i++){
        Node* newNode = new Node(testCase[i]);
        obj.root = obj.insert(obj.root, newNode);
        cout << endl;
        obj.print2D(obj.root, 5);
    }

    return 0;
}