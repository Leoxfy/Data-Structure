#include <iostream>
using namespace std;

struct Format{
    string pre;
    int data;
    string suc;
    Format(){
        pre = "";
        data = 0;
        suc = "";
    }
    Format(string a, int b, string c){
        pre = a;
        data = b;
        suc = c;
    }
};
Format a[1000];

struct Node{
    string pre;
    int data;
    string suc;
    Node *next;
    Node(){
        data = 0;
        next = NULL;
    }
    Node(const Format& x){
        pre = x.pre;
        data = x.data;
        suc = x.suc;
        next = NULL;
    }
};

class LinkedList{
private:
    Node *first;
public:
    LinkedList();
    ~LinkedList();
    void Input(const Format& x);
    void Output();
    void Solve(LinkedList& right);
    void Solve2();
};
int main()
{
    string head;
    int n;
    LinkedList lst;
    LinkedList right;
    cin>>head>>n;
    for(int i=0;i<n;i++){
        cin>>a[i].pre;
        cin>>a[i].data;
        cin>>a[i].suc;
    }
    string cur = head;
    while(cur!="-1"){
        for(int i=0;i<n;i++){
            if(a[i].pre==cur){
                lst.Input(a[i]);
                cur = a[i].suc;
                break;
            }
        }
    }
    lst.Solve(right);
    lst.Solve2();
    right.Solve2();
    lst.Output();
    cout<<endl;
    right.Output();
    return 0;
}



LinkedList::LinkedList(){
    first = new Node;
}

LinkedList::~LinkedList(){
    Node *del = first->next;
    while(del!=NULL){
        first->next = del->next;
        delete del;
        del = first->next;
    }
}

void LinkedList::Input(const Format& x){
    Node *last = first;
    while(last->next!=NULL){
        last = last->next;
    }
    Node *newNode = new Node(x);
    last->next = newNode;
}


void LinkedList::Output(){
    Node *cur = first->next;
    while(cur->next!=NULL){
        cout<<cur->pre<<" "<<cur->data<<" "<<cur->suc<<endl;
        cur = cur->next;
    }
    cout<<cur->pre<<" "<<cur->data<<" "<<cur->suc;
}


void LinkedList::Solve(LinkedList& right){
    Node *pre = first;
    Node *cur = first->next;
    Format b[1000];
    int cnt = 0;
    int flag = 0;
    while(cur!=NULL){
        flag = 0;
        for(int i=0;i<cnt;i++){
            if(b[i].data==cur->data || b[i].data==-cur->data){
                flag = 1;

                Format data(cur->pre,cur->data,cur->suc);
                right.Input(data);
                pre->next = cur->next;
                delete cur;
                cur = pre->next;
                break;
            }
        }
        if(flag==0){
            b[cnt].pre = cur->pre;
            b[cnt].data = cur->data;
            b[cnt].suc = cur->suc;
            cnt++;
            pre = cur;
            cur = cur->next;
        }
    }
}


void LinkedList::Solve2(){
    if(first->next==NULL){
        return ;
    }
    Node *pre = first->next;
    Node *cur = pre->next;
    while(cur!=NULL){
        pre->suc = cur->pre;
        pre = cur;
        cur = cur->next;
    }
    pre->suc = "-1";
}
