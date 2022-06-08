#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
struct Data{
    int no;
    string name;
    double s1;
    double s2;
    double s3;
    double ave;
    Data(){}
    Data(int nn, string na, double ss1, double ss2, double ss3){
        no = nn;
        name = na;
        s1 = ss1;
        s2 = ss2;
        s3 = ss3;
        ave = (s1+s2+s3)/3;
    }
};
struct Node{
    Data data;
    Node *next;
    Node(Data& d):data(d){
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
    int Length();
    void Sort();
};

int main()
{
    int n;
    cin>>n;
    LinkedList lst;
    lst.Input(n);
    lst.Sort();
    lst.OutPut();
    return 0;
}


LinkedList::LinkedList(){
    Data d;
    first = new Node(d);
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
        int no;
        string name;
        double s1, s2, s3;
        cin>>no>>name>>s1>>s2>>s3;
        Data dd(no,name,s1,s2,s3);

        Node *newNode = new Node(dd);
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
    int i=1;
    while(cur!=NULL){
        cout.setf(ios::fixed);
        cout<<cur->data.no<<" "<<cur->data.name<<" "
        <<fixed<<setprecision(2)<<cur->data.s1<<" "<<cur->data.s2<<" "
        <<cur->data.s3<<" "<<cur->data.ave<<" "
        <<i<<endl;
        i++;
        cur = cur->next;
    }
    cout<<endl;
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


void LinkedList::Sort(){
    int len = Length();
    if(len<=1){
        return ;
    }

    for(int i=1;i<len;i++){
        Node *pp = first;
        Node *pre = pp->next;
        Node *cur = pre->next;
        while(cur!=NULL){
            if(cur->data.ave > pre->data.ave){
                pp->next = cur;
                pre->next = cur->next;
                cur->next = pre;
                pre = cur;
                cur = pre->next;
            }
            pp = pp->next;
            pre = pre->next;
            cur = cur->next;
        }
    }
    return ;
}
