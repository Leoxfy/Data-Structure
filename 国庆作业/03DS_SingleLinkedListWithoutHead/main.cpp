#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef int T;
//没有附加头节点的链表
struct LinkNode //结点定义
{
      T data;//数据域
      LinkNode* next;//链域


      LinkNode(const T& item, LinkNode* ptr=NULL)
      {
            data=item;
            next=ptr;
      }
      LinkNode(LinkNode* ptr=NULL)
      {
            next=ptr;
      }
};



class List
{
private:
      LinkNode * first;


public:
      List();//构造函数
      //List(const T& x);
//      List(int n,);
      List(const List& L);//拷贝构造函数
      List& operator=(const List& L);//赋值运算符函数
      ~List();//析构函数

      void InputFront(const T& elem);//头插法
      void InputRear(const T& elem);//尾插法

      void MakeEmpty();//清空链表
      int Length() const;//返回链表中结点个数

      LinkNode* Search(const T& x);//在链表中查找元素x，找到返回它所在结点的地址，否则返回空
      LinkNode* Locate(int i);//返回链表中第i个结点的地址，i取值不合法则返回空

      bool GetData(int i, T& x)const;//获取链表第i个元素，将它赋值给x
      void SetData(int i, const T& x);//设置链表第i个元素为x

      bool Insert(int i, const T& x);//在链表的第i个位置上插入元素x
      bool Remove(int i, T& x);//删除链表第i个位置的元素，并将它的值赋值给x

      bool IsEmpty() const;//返回链表是否为空
      bool IsFull() const;//返回链表是否为满
      void CopyList(const List& L);//复制链表
      void Sort();//对链表中结点进行排序
      friend ostream& operator<<(ostream& out, const List& L);//输出流运算符重载
      friend istream& operator>>(istream& in, List& L);//输入流运算符重载
};

int main()
{
      List lst;
      srand(time(NULL));
      for(int i=1; i<=10; i++)
            lst.Insert(i,rand()%50);
      lst.Sort();
      cout<<lst;
      int val;
      lst.Remove(2,val);
      cout<<lst;
      List lst1=lst;
      lst.MakeEmpty();
      lst=lst1;
      cout<<lst;
}




List::List(){
    first = NULL;
}


void List::InputFront(const T& elem){
    T temp;
    cin>>temp;
    while(temp!=elem){
        LinkNode *newNode = new LinkNode(temp);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        newNode->next = first;
        first = newNode;

        cin>>temp;
    }
    return;
}



void List::InputRear(const T& elem){
    LinkNode *last = first;
    if(first!=NULL){
        while(last->next!=NULL){
            last = last->next;
        }
    }

    T temp;
    cin>>temp;
    while(temp!=elem){
        LinkNode *newNode = new LinkNode(temp);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        if(first==NULL){
            newNode->next = first;
            first = newNode;
            last = newNode;
        }else{
            newNode->next = last->next;
            last->next = newNode;
            last = newNode;
        }
        cin>>temp;
    }
    return;
}


void List::MakeEmpty(){
    LinkNode *del = first;
    while(del!=NULL){
        first = del->next;
        delete del;
        del = first;
    }
    return;
}


int List::Length() const{
    LinkNode *cur = first;
    int cnt = 0;
    while(cur!=NULL){
        cnt++;
        cur = cur->next;
    }
    return cnt;
}

LinkNode* List::Search(const T& x){
    LinkNode *cur = first;
    while(cur!=NULL){
        if(cur->data==x){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

LinkNode* List::Locate(int i){
    if(first==NULL || i<=0){
        return NULL;
    }
    LinkNode *cur = first;
    for(int j=1;j<i;j++){
        if(cur==NULL){
            return NULL;
        }
        cur = cur->next;
    }
    return cur;
}


bool List::GetData(int i, T& x)const{
    if(first==NULL || i<=0){
        return false;
    }
    LinkNode *cur = first;
    for(int j=1;j<i;j++){
        if(cur==NULL){
            return false;
        }
        cur = cur->next;
    }
    x = cur->data;
    return true;
}


void List::SetData(int i, const T& x){
    if(first==NULL || i<=0){
        return ;
    }
    LinkNode *cur = first;
    for(int j=1;j<i;j++){
        if(cur==NULL){
            return ;
        }
        cur = cur->next;
    }
    cur->data = x;
    return ;
}


bool List::Insert(int i, const T& x){
    if(i<=0){
        return false;
    }

    LinkNode *newNode = new LinkNode(x);
    if(newNode==NULL){
        cerr<<"error!"<<endl;
        exit(1);
    }

    if(i==1){
        newNode->next = first;
        first = newNode;
        return true;
    }
    LinkNode *cur = first;
    for(int j=1;j<i-1;j++){
        if(cur==NULL){
            return false;
        }
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return true;
}

bool List::Remove(int i, T& x){
    if(first==NULL || i<=0){
        return false;
    }
    if(i==1){
        LinkNode *del = first;
        first = del->next;
        x = del->data;
        delete del;
        return true;
    }
    LinkNode *cur = first;
    for(int j=1;j<i-1;j++){
        if(cur==NULL){
            return false;
        }
        cur = cur->next;
    }
    if(cur->next==NULL){
        return false;
    }
    LinkNode *del = cur->next;
    cur->next = del->next;
    x = del->data;
    delete del;
    return true;
}



bool List::IsEmpty() const{
    return first==NULL ? true:false;
}



bool List::IsFull() const{
    return false;
}



void List::CopyList(const List& L){
    MakeEmpty();
    if(L.first==NULL){
        return;
    }
    LinkNode *src = L.first;
    LinkNode *des = NULL;
    LinkNode *newNode = new LinkNode(src->data);
    first = newNode;
    src = src->next;
    des = first;

    while(src!=NULL){
        LinkNode *newNode = new LinkNode(src->data);
        des->next = newNode;

        des = des->next;
        src = src->next;
    }
}


List::List(const List& L){
    first = NULL;
    CopyList(L);
}

List& List::operator=(const List& L){
    if(&L==this){
        return *this;
    }
    CopyList(L);
    return *this;
}



List::~List(){
    MakeEmpty();
}



void List::Sort(){
    int len = Length();
    if(len<=1){
        return ;
    }
    for(int i=1;i<len;i++){
        LinkNode *pre = first;
        LinkNode *cur = pre->next;
        while(cur!=NULL){
            if(cur->data<pre->data){
                T t;
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



istream& operator>>(istream& in, List& L){
    int mode = 0;
    cout<<"请选择插入方式：0）头插法 1）尾插法"<<endl;
    cin>>mode;
    while(mode!=0 || mode!=1){
        cout<<"方式选择错误，请重新输入："<<endl;
        cin>>mode;
    }
    cout<<"输入结束标志为0："<<endl;

    if(mode==0){
        L.InputFront(0);
        return in;
    }else{
        L.InputRear(0);
        return in;
    }
}



ostream& operator<<(ostream& out, const List& L){
    LinkNode *cur = L.first;
    if(cur==NULL){
        out<<"单链表为空表"<<endl;
        return out;
    }
    cout<<"单链表如下："<<endl;
    while(cur!=NULL){
        out<<cur->data<<" ";
        cur = cur->next;
    }
    cout<<endl;
    return out;
}
