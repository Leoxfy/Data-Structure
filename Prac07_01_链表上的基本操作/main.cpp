#include <iostream>
using namespace std;
struct Node{
    int data;
    Node *next;
    Node(int x){
        data = x;
        next = NULL;
    }
    Node(){
        data = 0;
        next = NULL;
    }
};
class LinkedList{
private:
    Node *first;
public:
    LinkedList();
    ~LinkedList();
    void create(int n);
    void print();
    void insertN(int x, int n);
    void deleteN(int n);
    void searchN(int x);
    void reverseN();
};
LinkedList::LinkedList(){
    first = NULL;
}
LinkedList::~LinkedList(){
    if(first==NULL){
        return ;
    }
    Node *del = first;
    while(first->next!=NULL){
        first = del->next;
        delete del;
        del = first;
    }
    delete first;
}
void LinkedList::create(int n){
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        Node *newNode = new Node(x);
        if(first==NULL){
            first = newNode;
        }else{
            Node *cur = first;
            while(cur->next!=NULL){
                cur = cur->next;
            }
            cur->next = newNode;
        }
    }
}
void LinkedList::print(){
    if(first==NULL){
        return ;
    }
    Node *cur = first;
    while(cur!=NULL){
        cout<<cur->data<<" ";
        cur = cur->next;
    }
    cout<<endl;
}
void LinkedList::insertN(int x, int n){
    Node *newNode = new Node(x);
    //暂时不考虑表空的情况
    if(n==1){
        newNode->next = first;
        first = newNode;
        return ;
    }
    Node *cur = first;
    for(int i=1;i<n-1;i++){
        if(cur==NULL){
            return ;
        }
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
}
void LinkedList::deleteN(int n){
    //暂时不考虑表空的情况
    if(n==1){
        Node *del = first;
        first = del->next;
        delete del;
        return ;
    }
    Node *cur = first;
    for(int i=1;i<n-1;i++){
        if(cur->next==NULL){
            return ;
        }
        cur = cur->next;
    }
    Node *del = cur->next;
    cur->next = del->next;
    delete del;
    return ;
}
void LinkedList::searchN(int x){
    if(first==NULL){
        return ;
    }
    Node *cur = first;
    int cnt = 1;
    while(1){
        if(cur==NULL){
            cout<<"Not found"<<endl;
            return ;
        }
        if(cur->data==x){
            cout<<cnt<<endl;
            return ;
        }
        cur = cur->next;
        cnt++;
    }
}
void LinkedList::reverseN(){
    //先不考虑表长小于3的情况
    Node *pre = first;
    Node *cur = first->next;
    Node *suc = cur->next;
    while(cur!=NULL){
        cur->next = pre;
        pre = cur;
        cur = suc;
        suc = suc->next;
    }
    first = pre;
    return ;
}
int main()
{
    int n, x;
    cin>>n;
    LinkedList list1;
    list1.create(n);
    cin>>x>>n;
    list1.insertN(x, n);
    list1.print();
    cin>>n;
    list1.deleteN(n);
    list1.print();
    cin>>x;
    list1.searchN(x);
    list1.reverseN();
    list1.print();
    return 0;
}
