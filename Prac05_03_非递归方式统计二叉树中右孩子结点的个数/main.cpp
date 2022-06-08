#include <iostream>
using namespace std;
int cnt = 0;
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
    //记住：传递参数要用*& 指针的引用
    BinTree();
    ~BinTree();
    void destory(Node *subTree);
    void createBinTree(Node *&subTree);
    void preOrder(Node *subTree);
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
    delete root;
}
void BinTree::createBinTree(Node * &subTree){
    char x;
    cin>>x;

    if(x=='@'){
        subTree = NULL;
        return ;
    }
    subTree = new Node(x);
    createBinTree(subTree->leftChild);
    createBinTree(subTree->rightChild);
}

void BinTree::preOrder(Node *subTree){
    if(subTree==NULL){
        return ;
    }
    preOrder(subTree->leftChild);
    if(subTree->rightChild!=NULL){
        cnt++;
    }
    preOrder(subTree->rightChild);
}


int main()
{
    BinTree tree;
    tree.createBinTree(tree.root);
    tree.preOrder(tree.root);
    cout<<cnt;
    return 0;
}
