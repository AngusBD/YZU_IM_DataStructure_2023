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

    Node* insert(Node* currentNode, Node* newNode){
        if(currentNode == NULL){
            currentNode = newNode;
            cout << "insertComplete!" << endl;
            return currentNode;
        }

        if(newNode->value < currentNode->value){
            currentNode->left = insert(currentNode->left, newNode);
        }
        else if(newNode->value > currentNode->value){
            currentNode->right = insert(currentNode->right, newNode);
        }
        else{
            cout << "insertError!" << endl;
            return currentNode;
        }

        int bf = getBalanceFactor(currentNode);
        // LL Case
        if(bf > 1 && newNode->value < currentNode->left->value){
            return rightRotate(currentNode);
        }

        //RR Case
        if(bf < -1 && newNode->value > currentNode->right->value){
            return leftRotate(currentNode);
        }

        //LR Case
        if(bf > 1 && newNode->value > currentNode->left->value){
            currentNode->left = leftRotate(currentNode->left);
            return rightRotate(currentNode);
        }

        //RL Case
        if(bf < -1 && newNode->value < currentNode->right->value){
            currentNode->right = rightRotate(currentNode->right);
            return leftRotate(currentNode);
        }

        return currentNode;
    }

    Node* minValueNode(Node* node){
        Node* current = node;

        while(current->left != NULL){
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* currentNode, int val){
        if(currentNode == NULL){
            return NULL;
        }

        else if(val < currentNode->value){
            currentNode->left = deleteNode(currentNode->left, val);
        }

        else if(val > currentNode->value){
            currentNode->right = deleteNode(currentNode->right, val);
        }

        else{
            //node with only one child or no child
            if(currentNode->left == NULL){
                Node* tempNode = currentNode->right;
                delete currentNode;
                return tempNode;
            }
            else if(currentNode->right == NULL){
                Node* tempNode = currentNode->left;
                delete currentNode;
                return tempNode;
            }
            else{
                //node with two children: Get the inorder successor (smallest in the right subtree)
                Node* tempNode = minValueNode(currentNode->right);
                //copy the inorder successor's content to this node
                currentNode->value = tempNode->value;
                //delete the inorder successor
                currentNode->right = deleteNode(currentNode->right, tempNode->value);
            }
        }

        int bf = getBalanceFactor(currentNode);

        //LL Case
        if(bf == 2 && getBalanceFactor(currentNode->left) >= 0){
            return rightRotate(currentNode);
        }
        //RR Case
        else if(bf == -2 && getBalanceFactor(currentNode->right) <= 0){
            return leftRotate(currentNode);
        }
        //LR Case
        else if(bf == 2 && getBalanceFactor(currentNode->left) == -1){
            currentNode->left = leftRotate(currentNode->left);
            return rightRotate(currentNode);
        }
        //RL Case
        else if(bf == -2 && getBalanceFactor(currentNode->right) == 1){
            currentNode->right = rightRotate(currentNode->right);
            return leftRotate(currentNode);
        }

        return currentNode;
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
        cout << "\n______________________________\n";
    }
    obj.deleteNode(obj.root, 32);
    obj.print2D(obj.root, 5);
    return 0;
}