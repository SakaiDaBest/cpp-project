#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data){
    Node* newNode = new Node();
    newNode -> data = data;
    newNode->left =newNode->right = nullptr;//add left and right
    return newNode;
}

int main(){
    Node* root=createNode(1);//root
    root->left=createNode(2);
    root->right=createNode(3);
    root->left->left=createNode(4);
}