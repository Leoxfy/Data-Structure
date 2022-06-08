#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

vector<int> codeStack;
map<char, int> dic;

struct Node{
    int weight;
    char data;
    Node *parent;
    Node *leftChild;
    Node *rightChild;
    Node(char ch, int w){
        data = ch;
        weight = w;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
    Node(){
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
};
struct cmp{
    bool operator()(Node *a, Node *b){
        return a->weight > b->weight;
    }
};

struct codeResult{
    char ch;
    int weight;
    string code;
};

codeResult arr[1000];

Node* mergeNode(Node*& first, Node*& second){
    Node *newNode = new Node;
    newNode->weight = first->weight + second->weight;
    newNode->data = '0';
    newNode->parent = newNode;
    newNode->leftChild = first;
    newNode->rightChild = second;
    first->parent = newNode;
    second->parent = newNode;
    return newNode;
}

void destory(Node *subTree){
    if(subTree==NULL){
        return ;
    }
    destory(subTree->leftChild);
    destory(subTree->rightChild);
    delete subTree;
}
int t = 0;
void preOrder(Node *subTree){
    if(subTree==NULL){
        return ;
    }
    if(subTree->leftChild==NULL && subTree->rightChild==NULL){
        string temp = "";
        for(auto it=codeStack.begin();it!=codeStack.end();it++){
            temp += to_string(*it);
        }
        arr[t].ch = subTree->data;
        arr[t].weight = dic[subTree->data];
        arr[t].code = temp;
        t++;
    }
    codeStack.push_back(0);
    preOrder(subTree->leftChild);
    codeStack.pop_back();
    codeStack.push_back(1);
    preOrder(subTree->rightChild);
    codeStack.pop_back();
}

int cmp2(codeResult a, codeResult b){
    return a.weight > b.weight;
}

priority_queue<Node *, vector<Node *>, cmp > q;


int main()
{
    int n;
    cin>>n;
    char x;
    for(int i=0;i<n;i++){
        cin>>x;
        auto it = dic.find(x);
        if(it==dic.end()){
            dic[x] = 1;
        }else{
            dic[x]++;
        }
    }
    for(auto it = dic.begin();it!=dic.end();it++){
        Node *newNode = new Node(it->first,it->second);
        newNode->parent = newNode;
        q.push(newNode);
    }
    while(q.size()!=1){
        Node *first = q.top();
        q.pop();
        Node *second = q.top();
        q.pop();
        Node *parent = mergeNode(first,second);
        q.push(parent);
    }
    preOrder(q.top());
    sort(arr,arr+t,cmp2);
    for(int i=0;i<t;i++){
        cout<<arr[i].ch<<" "<<arr[i].weight<<" "<<arr[i].code<<endl;
    }
    destory(q.top());
    return 0;
}
