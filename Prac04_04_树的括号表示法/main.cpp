#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;
//书上P198页还有一种算法，栈只记录根结点，不记录子树，优美
struct Node{
    char data;
    Node *left;
    Node *right;
    Node(char x){
        data = x;
        left = NULL;
        right = NULL;
    }
};

class BinTree{
public:
    Node *root;
    BinTree();
    ~BinTree();
    void destory(Node *subTree);
    void createBinTree(string str);
    void preOrder(Node *subTree);
    void levelOrder();
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
    destory(subTree->left);
    destory(subTree->right);
    delete subTree;
}

void BinTree::createBinTree(string str){
    Node *sroot = NULL;
    Node *pre = NULL;
    int mode;
    stack<Node *> s;

    for(int i=0;i<(int)str.length();i++){
        if(str[i]=='('){
            mode = 0;

        }else if(str[i]==')'){
            sroot = s.top();
            s.pop();
            //如果根外面也有（）这一步就要写
            if(s.empty()){
                break;
            }
            pre = s.top();
            while(pre->right==sroot){
                sroot = pre;
                s.pop();
                pre = s.top();
            }

        }else if(str[i]==','){
            mode = 1;

        }else{
            sroot = new Node(str[i]);

            if(root==NULL){
                root = sroot;
            }else{
                pre = s.top();
                if(mode==0){
                    pre->left = sroot;
                }else if(mode==1){
                    pre->right = sroot;
                }
            }

            s.push(sroot);

        }
    }

}
void BinTree::preOrder(Node *subTree){
    if(subTree==NULL){
        return ;
    }
    cout<<subTree->data;
    preOrder(subTree->right);
    preOrder(subTree->left);
}

void BinTree::levelOrder(){
    queue<Node *> que;
    que.push(root);
    while(!que.empty()){
        Node *cur = que.front();
        if(cur->left!=NULL){
            Node *suc = cur->left;
            que.push(suc);
            while(suc->right!=NULL){
                suc = suc->right;
                que.push(suc);
            }
        }
        cout<<cur->data;
        que.pop();
    }
}
int main()
{
    string str;
    cin>>str;
    BinTree tree;
    tree.createBinTree(str);
    tree.levelOrder();
    return 0;
}
