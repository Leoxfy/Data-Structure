#include <iostream>
#include <queue>
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

class BinaryTree{
private:
    Node *root;
public:
    BinaryTree();
    ~BinaryTree();
    void destory(Node *subTree);
    void postOrder(Node *subTree, void (*visit)(Node *));
    void setRoot(Node *newRoot);
    Node* getroot();
    void levelOrder(void (*visit)(Node *));
};

BinaryTree::BinaryTree(){
    root = NULL;
}


BinaryTree::~BinaryTree(){
    destory(root);
}

void BinaryTree::destory(Node *subTree){
    if(subTree==NULL){
        return ;
    }
    destory(subTree->leftChild);
    destory(subTree->rightChild);
    delete subTree;
}

void BinaryTree::postOrder(Node *subTree, void (*visit)(Node *) ){
    if(subTree==NULL){
        return ;
    }
    postOrder(subTree->leftChild, visit);
    postOrder(subTree->rightChild, visit);
    visit(subTree);
}

void BinaryTree::setRoot(Node *newRoot){
    root = newRoot;
}

Node* BinaryTree::getroot(){
    return root;
}

void BinaryTree::levelOrder(void (*visit)(Node *)){
    queue<Node*> que;
    que.push(root);
    while(!que.empty()){
        Node* top = que.front();
        que.pop();
        visit(top);
        if(top->leftChild!=NULL){
            que.push(top->leftChild);
        }
        if(top->rightChild!=NULL){
            que.push(top->rightChild);
        }
    }
}

Node* creatBinTree(int *VLR, int *LVR, int n){
    if(n==0){
        return NULL;
    }
    int k = 0;
    while(VLR[0] != LVR[k]){
        k++;
    }
    Node *newTree = new Node(VLR[0]);
    newTree->leftChild = creatBinTree(VLR+1, LVR, k);
    newTree->rightChild = creatBinTree(VLR+k+1, LVR+k+1, n-1-k);
    return newTree;
}


void out(Node * now){
    cout<<now->data<<" ";
}

int main()
{
    int n;
    cin>>n;
    int *VLR = new int[n];
    int *LVR = new int[n];
    for(int i=0;i<n;i++){
        cin>>VLR[i];
    }
    for(int i=0;i<n;i++){
        cin>>LVR[i];
    }
    Node *root = creatBinTree(VLR, LVR, n);

    BinaryTree tree;
    tree.setRoot(root);


    tree.levelOrder(out);
    cout<<endl;
    tree.postOrder(tree.getroot(), out);
    cout<<endl;
    delete[] VLR;
    delete[] LVR;
    return 0;
}
