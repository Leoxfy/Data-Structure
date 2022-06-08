#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef int T;
//û�и���ͷ�ڵ������
struct LinkNode //��㶨��
{
      T data;//������
      LinkNode* next;//����


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
      List();//���캯��
      //List(const T& x);
//      List(int n,);
      List(const List& L);//�������캯��
      List& operator=(const List& L);//��ֵ���������
      ~List();//��������

      void InputFront(const T& elem);//ͷ�巨
      void InputRear(const T& elem);//β�巨

      void MakeEmpty();//�������
      int Length() const;//���������н�����

      LinkNode* Search(const T& x);//�������в���Ԫ��x���ҵ����������ڽ��ĵ�ַ�����򷵻ؿ�
      LinkNode* Locate(int i);//���������е�i�����ĵ�ַ��iȡֵ���Ϸ��򷵻ؿ�

      bool GetData(int i, T& x)const;//��ȡ�����i��Ԫ�أ�������ֵ��x
      void SetData(int i, const T& x);//���������i��Ԫ��Ϊx

      bool Insert(int i, const T& x);//������ĵ�i��λ���ϲ���Ԫ��x
      bool Remove(int i, T& x);//ɾ�������i��λ�õ�Ԫ�أ���������ֵ��ֵ��x

      bool IsEmpty() const;//���������Ƿ�Ϊ��
      bool IsFull() const;//���������Ƿ�Ϊ��
      void CopyList(const List& L);//��������
      void Sort();//�������н���������
      friend ostream& operator<<(ostream& out, const List& L);//��������������
      friend istream& operator>>(istream& in, List& L);//���������������
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
    cout<<"��ѡ����뷽ʽ��0��ͷ�巨 1��β�巨"<<endl;
    cin>>mode;
    while(mode!=0 || mode!=1){
        cout<<"��ʽѡ��������������룺"<<endl;
        cin>>mode;
    }
    cout<<"���������־Ϊ0��"<<endl;

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
        out<<"������Ϊ�ձ�"<<endl;
        return out;
    }
    cout<<"���������£�"<<endl;
    while(cur!=NULL){
        out<<cur->data<<" ";
        cur = cur->next;
    }
    cout<<endl;
    return out;
}
