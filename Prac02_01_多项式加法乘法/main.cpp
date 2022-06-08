#include <iostream>
using namespace std;
struct Data{
    int k;
    int exp;
    Data(int a, int b){
        k = a;
        exp = b;
    }
    Data(){
        k = 0;
        exp = 0;
    }
};
struct Node{
    Data data;
    Node *next;
    Node(){
        Data d;
        data = d;
        next = NULL;
    }
    Node(const Data& d):data(d){
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
    void InputRear(const Data& data);
    friend LinkedList operator+(LinkedList& left, LinkedList& right);
    friend LinkedList operator*(LinkedList& left, LinkedList& right);
    LinkedList& operator=(LinkedList& right);
    friend ostream& operator<<(ostream& out, const LinkedList& right);
};
int main()
{
    //考虑一下0多项式
    int n1;
    LinkedList list1;
    cin>>n1;
    int k,exp;
    for(int i=0;i<n1;i++){
        cin>>k>>exp;
        Data d(k,exp);
        list1.InputRear(d);
    }
    int n2;
    LinkedList list2;
    cin>>n2;
    for(int i=0;i<n2;i++){
        cin>>k>>exp;
        Data d(k,exp);
        list2.InputRear(d);
    }

    cout<<list1 * list2<<endl;
    cout<<list1 + list2;
    return 0;
}


LinkedList::LinkedList(){
    first = new Node;
}

LinkedList::~LinkedList(){
    MakeEmpty();
    delete first;
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

void LinkedList::InputRear(const Data& data){
    Node *last = first;
    while(last->next!=NULL){
        last = last->next;
    }
    Node *newNode = new Node(data);
    last->next = newNode;
    return ;
}


LinkedList& LinkedList::operator=(LinkedList& right){
    MakeEmpty();
    Node *src = right.first->next;
    Node *last = first;
    while(src!=NULL){
        Node *newNode = new Node(src->data);
        last->next = newNode;
        last = last->next;
        src = src->next;
    }
    return *this;
}

LinkedList operator+(LinkedList& left, LinkedList& right){
    LinkedList ans;
    Node *pl = left.first->next;
    Node *pr = right.first->next;
    while(pl!=NULL && pr!=NULL){
        //比较两个指针的指数大小
        //如果相等，相加，判断是否为0,两个指针均右移动
        //如果不相等，指数大者加入ans，指针右移动
        if(pl->data.exp==pr->data.exp){
            int exp = pl->data.exp;
            int k = pl->data.k + pr->data.k;
            if(k!=0){
                Data newData(k,exp);
                ans.InputRear(newData);
            }
            pl = pl->next;
            pr = pr->next;
        }else if(pl->data.exp > pr->data.exp){
            Data newDate(pl->data.k, pl->data.exp);
            ans.InputRear(newDate);
            pl = pl->next;
        }else{
            Data newDate(pr->data.k, pr->data.exp);
            ans.InputRear(newDate);
            pr = pr->next;
        }
    }
    if(pl!=NULL){
        while(pl!=NULL){
            Data newDate(pl->data.k, pl->data.exp);
            ans.InputRear(newDate);
            pl = pl->next;
        }
    }
    if(pr!=NULL){
        while(pr!=NULL){
            Data newDate(pl->data.k, pl->data.exp);
            ans.InputRear(newDate);
            pl = pl->next;
        }
    }
    return ans;
}


LinkedList operator*(LinkedList& left, LinkedList& right){
    LinkedList ans;
    Node *pl = left.first->next;
    Node *pr = right.first->next;
    //使用辅助数组暂存结果
    //考虑0多项式和常数多项式
    if(pl==NULL || pr==NULL){
        return ans;
    }
    int lmax = pl->data.exp;
    int rmax = pr->data.exp;
    int maxexp = lmax + rmax;
    int *result = new int[maxexp+1];
    for(int i=0;i<=maxexp;i++){
        result[i] = 0;
    }

    while(pl!=NULL){
        while(pr!=NULL){
            int exp = pl->data.exp + pr->data.exp;
            int k = pl->data.k * pr->data.k;
            result[exp] += k;
            pr = pr->next;
        }
        pl = pl->next;
        pr = right.first->next;
    }
    for(int i=maxexp;i>=0;i--){
        if(result[i]!=0){
            Data d(result[i], i);
            ans.InputRear(d);
        }
    }
    delete[] result;
    return ans;
}


ostream& operator<<(ostream& out, const LinkedList& right){
    Node *cur = right.first->next;
    if(cur==NULL){
        out<<"0 0";
        return out;
    }
    while(cur->next!=NULL){
        out<<cur->data.k<<" "<<cur->data.exp<<" ";
        cur = cur->next;
    }
    out<<cur->data.k<<" "<<cur->data.exp;
    return out;
}
