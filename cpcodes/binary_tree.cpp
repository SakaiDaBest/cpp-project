#include <bits/stdc++.h>
using namespace std;

struct Node{//left small right big 
    int data;
    Node* left;
    Node* right;
};
Node* root;
root=null;
Node* createNode(Node* root,int data){
    if(root ==NULL){
        root = (data);
        return root;
    }else if(data<=root->data){
        root->left=createNode(root->left,data);
    }else{
        root->right=createNode(root->right,data);
    }
    Node* newNode = new Node();
    newNode -> data = data;
    newNode->left =newNode->right = nullptr;//add left and right
    return newNode;
}
bool Search(Node* root,int data){

}

int main(){
    Node* root = NULL;
    createNode(root,15);
    createNode(root,10);
    createNode(root,20);
}