#include <iostream>
using namespace std;
int a[1000];
int n = 0;
struct Node{
    int data;
    Node *next;
    Node(){
        data = 0;
        next = NULL;
    }
    Node(int i){
        data = i;
        next = NULL;
    }
};
class LinkedList{
private:
    Node *first;
public:
    LinkedList();
    ~LinkedList();
    void Input();
    void Solve(const LinkedList& right);
};
int main()
{
    LinkedList s1;
    LinkedList s2;
    s1.Input();
    s2.Input();
    s1.Solve(s2);
    if(n==0){
        cout<<"NULL";
    }else{
        for(int i=0;i<n-1;i++){
            cout<<a[i]<<" ";
        }
        cout<<a[n-1];
    }
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
    delete first;
}

void LinkedList::Input(){
    int x;
    Node *last = first;
    while(1){
        cin>>x;
        if(x==-1){
            break;
        }
        Node *newNode = new Node(x);
        last->next = newNode;
        last = last->next;
    }
    return ;
}

void LinkedList::Solve(const LinkedList& right){
    Node *pl = first->next;
    Node *pr = right.first->next;
    while(pl!=NULL){
        pr = right.first->next;
        while(pr!=NULL){
            if(pr->data==pl->data){
                a[n] = pr->data;
                n++;
            }
            pr = pr->next;
        }
        pl = pl->next;
    }
    return ;
}
