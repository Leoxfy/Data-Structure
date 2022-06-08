#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *leftChild;
    Node *rightChild;
    Node(int x){
        data = x;
        leftChild = NULL;
        rightChild = NULL;
    }
};

class BinTree{
public:
    Node *root;

    BinTree();
    ~BinTree();
    void destory(Node *subTree);
    void preOrder(Node *subTree, void (*visit)(Node *));
    void postOrder(Node *subTree, void (*visit)(Node *));
    void createBinTree(int *level, int *LVR, int n);

};


BinTree::BinTree(){
    root = NULL;
}


BinTree::~BinTree(){
    destory(root);
}


void BinTree::destory(Node *subTree){
    if(subTree==NULL){
        return ;
    }
    destory(subTree->leftChild);
    destory(subTree->rightChild);
    delete subTree;
}

void BinTree::preOrder(Node *subTree, void (*visit)(Node *)){
    if(subTree==NULL){
        return ;
    }
    visit(subTree);
    preOrder(subTree->leftChild, visit);
    preOrder(subTree->rightChild, visit);
}

void BinTree::postOrder(Node *subTree, void (*visit)(Node *)){
    if(subTree==NULL){
        return ;
    }
    postOrder(subTree->leftChild, visit);
    postOrder(subTree->rightChild, visit);
    visit(subTree);
}


int pos(int x, int *a, int n){
    for(int i=0;i<n;i++){
        if(a[i]==x){
            return i;
        }
    }
    return -1;
}

void BinTree::createBinTree(int *level, int *LVR, int n){
    root = new Node(level[0]);
    Node *sroot = root;
    Node *pre = NULL;
    int mode;
    for(int i=1;i<n;i++){
        while(sroot!=NULL){
            if(pos(level[i], LVR, n) <pos(sroot->data, LVR, n)){
                mode = 0;
                pre = sroot;
                sroot = sroot->leftChild;
            }else{
                mode = 1;
                pre = sroot;
                sroot = sroot->rightChild;
            }
        }
        if(mode==0){
            pre->leftChild = new Node(level[i]);
        }else{
            pre->rightChild = new Node(level[i]);
        }
        sroot = root;
        pre = NULL;
    }
}

void out(Node *node){
    cout<<node->data<<" ";
}


int main()
{
    BinTree tree;
    int level[10000];
    int LVR[10000];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>level[i];
    }
    for(int i=0;i<n;i++){
        cin>>LVR[i];
    }
    tree.createBinTree(level,LVR,n);
    tree.preOrder(tree.root, out);
    cout<<endl;
    tree.postOrder(tree.root, out);
    return 0;
}
