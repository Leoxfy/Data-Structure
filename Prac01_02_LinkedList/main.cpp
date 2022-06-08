#include <iostream>
using namespace std;
struct Node{
    int data;
    Node *next;
    Node(){
        data = 0;
        next = NULL;
    }
    Node(int x){
        data = x;
        next = NULL;
    }
};
class LinkedList{
private:
    Node *first;
public:
    LinkedList();
    ~LinkedList();
    void MakeEmpty();
    void Input(int n);
    void OutPut();
    bool Insert(int i, const int& x);
    bool Remove(int i, int& x);
    int Search(int& x);
    int Length();
    void Reverse();
    void Add(const LinkedList& L);
    void Sort();
};
int main()
{
    int n, i, x;
    cin>>n;
    LinkedList lst;
    lst.Input(n);
    cin>>x>>i;
    lst.Insert(i,x);
    lst.OutPut();
    cin>>i;
    lst.Remove(i,x);
    lst.OutPut();
    cin>>x;
    int b = lst.Search(x);
    if(b==0){
        cout<<"Not found"<<endl;
    }else{
        cout<<b<<endl;
    }
    lst.Reverse();
    lst.OutPut();
    cin>>n;
    LinkedList c;
    c.Input(n);
    lst.Add(c);
    lst.Sort();
    lst.OutPut();
    return 0;
}


LinkedList::LinkedList(){
    first = new Node;
    if(first==NULL){
        exit(1);
    }
}

void LinkedList::MakeEmpty(){
    Node *del = first->next;
    while(del!=NULL){
        first->next = del->next;
        delete del;
        del = first->next;
    }
    return ;
}

LinkedList::~LinkedList(){
    MakeEmpty();
    delete first;
}
void LinkedList::Input(int n){
    Node *last = first;
    for(int i=0;i<n;i++){
        int t;
        cin>>t;
        Node *newNode = new Node(t);
        if(newNode==NULL){
            exit(1);
        }
        last->next = newNode;
        last = last->next;
    }
}
void LinkedList::OutPut(){
    if(first->next==NULL){
        return ;
    }
    Node *cur = first->next;
    while(cur!=NULL){
        cout<<cur->data<<" ";
        cur = cur->next;
    }
    cout<<endl;
}

bool LinkedList::Insert(int i, const int& x){
    if(i<=0){
        return false;
    }
    Node *cur = first;
    for(int j=1;j<i;j++){
        if(cur==NULL){
            return false;
        }
        cur = cur->next;
    }
    Node *newNode = new Node(x);
    newNode->next = cur->next;
    cur->next = newNode;
    return true;
}

bool LinkedList::Remove(int i, int& x){
    if(i<=0 || first->next==NULL){
        return false;
    }
    Node *cur = first;
    for(int j=1;j<i;j++){
        if(cur==NULL || cur->next==NULL){
            return false;
        }
        cur = cur->next;
    }
    Node *del = cur->next;
    cur->next = del->next;
    x = del->data;
    delete del;
    return true;
}


int LinkedList::Search(int& x){
    if(first->next==NULL){
        return 0;
    }
    Node *cur = first->next;
    int cnt = 1;
    while(cur!=NULL){
        if(cur->data==x){
            return cnt;
        }
        cur = cur->next;
        cnt++;
    }
    return 0;
}
int LinkedList::Length(){
    if(first->next==NULL){
        return 0;
    }
    Node *cur = first->next;
    int cnt = 1;
    while(cur!=NULL){
        cur = cur->next;
        cnt++;
    }
    return cnt;
}
void LinkedList::Reverse(){
    if(Length()<=1){
        return ;
    }
    Node *pre = first;
    Node *cur = pre->next;
    Node *suc = cur->next;
    cur->next = NULL;
    pre = cur;
    cur = suc;
    suc = suc->next;
    while(1){
        cur->next = pre;
        pre = cur;
        cur = suc;
        if(cur==NULL){
            break;
        }
        suc = suc->next;
    }
    first->next = pre;
}


void LinkedList::Add(const LinkedList& L){
    if(L.first->next==NULL){
        return ;
    }
    Node *last = first;
    while(last->next!=NULL){
        last = last->next;
    }
    Node *src = L.first->next;
    while(src!=NULL){
        Node *newNode = new Node(src->data);
        last->next = newNode;
        last = last->next;
        src = src->next;
    }
    return ;
}

void LinkedList::Sort(){
    int len = Length();
    if(len==1){
        return ;
    }

    for(int i=1;i<len;i++){
        Node *pre = first->next;
        Node *cur = pre->next;
        while(cur!=NULL){
            if(cur->data < pre->data){
                int t;
                t = cur->data;
                cur->data = pre->data;
                pre->data = t;
            }
            pre = cur;
            cur = cur->next;
        }
    }
    return ;
}
