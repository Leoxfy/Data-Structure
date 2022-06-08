#include <iostream>
using namespace std;

int res[100];
int it = 0;

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
    res[it] = subTree->data;
    it++;
    preOrder(subTree->leftChild);
    preOrder(subTree->rightChild);
    return ;
}


BinTree::~BinTree(){
    destory(root);
}



Node* createBinTree(int *LRV, int *LVR, int n){
    if(n==0){
        return NULL;
    }

    //在中序中找到树根
    int k = 0;
    while(LRV[n-1]!=LVR[k]){
        k++;
    }

    //建立根结点
    Node *subTree = new Node(LRV[n-1]);

    //建立左右子树
    subTree->rightChild = createBinTree(LRV+k,LVR+k+1,n-1-k);
    subTree->leftChild = createBinTree(LRV,LVR,k);
    return subTree;

}

int a[100];
int b[100];
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

    tree.preOrder(tree.root);
    cout<<"Preorder: ";
    for(int i=0;i<n-1;i++){
        cout<<res[i]<<" ";
    }
    cout<<res[n-1];
    return 0;
}
