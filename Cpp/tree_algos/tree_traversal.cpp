/*
 *Program to print tree in inorder, pre-order and post-order
 * Ankit Goyal
 * Date: 10/12/2013
 *
 *
 * Example Tree:
 *
 *
 *                        0
 *                    1      3
 *                2
 *             4     5
 *                      6
 *                    7
 *
 *
 * inorder: 4 2 5 7 6 1 0 3
 * pre-order: 0 1 2 4 5 6 7 3
 * post-order: 4 7 6 5 2 1 3 0
 *
 * */

#include<iostream>


struct Node{
    int data;
    Node *left;
    Node *right;

    public:
    Node();
};

Node::Node(){
    left = NULL;
    right = NULL;
}

void inOrder(Node *root);
void preOrder(Node *root);
void postOrder(Node *root);
int countNodes(Node *root);



int main(void){
    struct Node root, n1, n2, n3, n4, n5, n6, n7;

    //construct example tree
    root.data = 0;
    n1.data = 1;
    n2.data = 2; n3.data = 3; n4.data = 4; n5.data = 5; n6.data = 6; n7.data = 7;
    root.left = &n1;
    n1.left = &n2;
    root.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n5.right = &n6;
    n6.left = &n7;

    //call inorder
    std::cout << "Inorder: ";
    inOrder(&root);

    //call pre-order
    std::cout << "\nPreorder: ";
    preOrder(&root);

    //call post-order
    std::cout << "\nPostorder: ";
    postOrder(&root);

    //node count
    std::cout << "\nNode Count: ";
    std::cout << countNodes(&root);

    return 0;
}

int countNodes(Node *root){
    int count = 0;
    if(root != NULL){
        count = 1; //count the root node
        count += countNodes(root -> left);
        count += countNodes(root -> right);
    }
    return count;
}

void inOrder(Node *root){
    if(root != NULL){
        inOrder(root->left);
        std::cout << root -> data;
        inOrder(root -> right);
    }
    return;
}

void preOrder(Node *root){
    if(root != NULL){
        std::cout << root -> data;
        preOrder(root->left);
        preOrder(root -> right);
    }
    return;
}

void postOrder(Node *root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root -> right);
        std::cout << root -> data;
    }
    return;
}
