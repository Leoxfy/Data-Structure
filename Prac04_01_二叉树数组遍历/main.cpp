#include <iostream>
using namespace std;
int *elem;
int length;

class BinaryTree{
public:
    BinaryTree(int n);
    ~BinaryTree();
    void inPut();
    void preOrder(int i, void (* visit)(int now));
    void inOrder(int i, void (* visit)(int now));
    void postOrder(int i, void (* visit)(int now));
};

BinaryTree::BinaryTree(int n){
    length = n;
    elem = new int[length];
}

BinaryTree::~BinaryTree(){
    delete [] elem;
}

void BinaryTree::inPut(){
    for(int i=0;i<length;i++){
        cin>>elem[i];
    }
}

void BinaryTree::preOrder(int i, void (* visit)(int now)){
    if(elem[i]==0){
        return ;
    }
    visit(i);
    if(2*i+1<length) preOrder(2*i+1, visit);
    if(2*i+2<length) preOrder(2*i+2, visit);
}

void BinaryTree::inOrder(int i, void (* visit)(int now)){
    if(elem[i]==0){
        return ;
    }
    if(2*i+1<length) inOrder(2*i+1, visit);
    visit(i);
    if(2*i+2<length) inOrder(2*i+2, visit);
}

void BinaryTree::postOrder(int i, void (* visit)(int now)){
    if(elem[i]==0){
        return ;
    }
    if(2*i+1<length) postOrder(2*i+1, visit);
    if(2*i+2<length) postOrder(2*i+2, visit);
    visit(i);
}

void visit(int now){
    cout<<elem[now]<<" ";
}

int main(){
    int n;
    cin>>n;
    BinaryTree tree(n);
    tree.inPut();
    void (* f)(int) = visit;
    tree.preOrder(0,f);
    cout<<endl;
    tree.inOrder(0,f);
    cout<<endl;
    tree.postOrder(0,f);
    cout<<endl;
    return 0;
}
