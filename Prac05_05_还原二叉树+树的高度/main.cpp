#include <iostream>
using namespace std;

struct Node{
    char data;
    Node *leftChild;
    Node *rightChild;

    Node(char x){
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
    void destory(Node  *subTree);
    void preOrder(Node *subTree);
};

BinTree::BinTree(){
    root = NULL;
}

void BinTree::destory(Node  *subTree){
    if(subTree==NULL){
        return ;
    }
    destory(subTree->leftChild);
    destory(subTree->rightChild);
    delete subTree;
    return ;
}

void BinTree::preOrder(Node *subTree){
    if(subTree==NULL){
        return ;
    }
    cout<<subTree->data<<" ";
    preOrder(subTree->leftChild);
    preOrder(subTree->rightChild);
    return ;
}

int getHeight(Node *subTree){
    if(subTree==NULL){
        return 0;
    }
    int a = getHeight(subTree->leftChild);
    int b = getHeight(subTree->rightChild);
    int c;
    if(a>b){
        c = a;
    }else{
        c = b;
    }
    return c+1;
}

BinTree::~BinTree(){
    destory(root);
}

Node* createBinTree(char *VLR, char *LVR, int n){
    if(n==0){
        return NULL;
    }
    //在中序中找到树根
    int k = 0;
    while(VLR[0]!=LVR[k]){
        k++;
    }

    //建立根结点
    Node *subTree = new Node(VLR[0]);

    //建立左右子树
    subTree->leftChild = createBinTree(VLR+1,LVR,k);
    subTree->rightChild = createBinTree(VLR+1+k,LVR+k+1,n-1-k);
    return subTree;

}

char a[100];
char b[100];
int main()
{
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    BinTree tree;
    tree.root = createBinTree(a,b,n);
    cout<<getHeight(tree.root);
    return 0;
}
