#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef int T;
//����ͷ�ڵ������
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
      for(int i=1; i<=10; i++){
            lst.Insert(i,rand()%50);
      }
      lst.Sort();
      cout<<lst;
      int val;
      lst.Remove(2,val);
      cout<<lst;
      List lst1=lst;
      lst.MakeEmpty();
      lst=lst1;
      cout<<lst;

      return 0;
}



List::List(){
    first = new LinkNode;
}


List::List(const List& L){
    first = new LinkNode;
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
    delete first;
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
        newNode->next = first->next;
        first->next = newNode;
        cin>>temp;
    }
    return ;
}



void List::InputRear(const T& elem){
    LinkNode *last = first;
    while(last->next!=NULL){
        last = last->next;
    }
    T temp;
    cin>>temp;
    while(temp!=elem){
        LinkNode *newNode = new LinkNode(temp);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }
        newNode->next = last->next;
        last->next = newNode;
        last = last->next;
        cin>>temp;
    }
    return ;
}

int List::Length() const{
    int cnt = 0;
    LinkNode *cur = first->next;
    while(cur!=NULL){
        cnt++;
        cur = cur->next;
    }
    return cnt;
}


LinkNode* List::Search(const T& x){
    LinkNode *cur = first->next;
    while(cur!=NULL){
        if(cur->data==x){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


LinkNode* List::Locate(int i){
    if(i<=0 || first->next==NULL){
        return NULL;
    }
    LinkNode *cur = first->next;
    for(int j=1;j<i;j++){
        if(cur==NULL){
            return NULL;
        }
        cur = cur->next;
    }
    return cur;
}

bool List::GetData(int i, T& x)const{
    if(i<=0 || first->next==NULL){
        return false;
    }
    LinkNode *cur = first->next;
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
    if(i<=0 || first->next==NULL){
        return;
    }
    LinkNode *cur = first->next;
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
    LinkNode *cur = first;
    for(int j=1;j<i;j++){
        if(cur==NULL){
            return false;
        }
        cur = cur->next;
    }
    LinkNode *newNode = new LinkNode(x);
    newNode->next = cur->next;
    cur->next = newNode;
    return true;
}

bool List::Remove(int i, T& x){
    if(i<=0 || first->next==NULL){
        return false;
    }
    LinkNode *cur = first;
    for(int j=1;j<i;j++){
        if(cur==NULL){
            return false;
        }
        cur = cur->next;
    }//������һ�����Ҫ������
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
    return first->next == NULL ? true:false;
}

bool List::IsFull() const{
    return false;
}

void List::CopyList(const List& L){
    MakeEmpty();
    LinkNode *src = L.first->next;
    LinkNode *des = first;
    while(src!=NULL){
        LinkNode *newNode = new LinkNode(src->data);
        if(newNode==NULL){
            cerr<<"error!"<<endl;
            exit(1);
        }

        newNode->next = des->next;
        des->next = newNode;


        des = des->next;
        src = src->next;
    }
    return;
}


void List::MakeEmpty(){
    LinkNode *del = first->next;
    while(del!=NULL){
        first->next = del->next;
        delete del;
        del = first->next;
    }
    return;
}

void List::Sort(){
    int len = Length();
    if(len>1){
        for(int i=1;i<len;i++){
            LinkNode *pre = first->next;
            LinkNode *cur = pre->next;
            while(cur!=NULL){
                if(cur->data < pre->data){
                    T t;
                    t = cur->data;
                    cur->data = pre->data;
                    pre->data = t;
                }
                pre = cur;
                cur = cur->next;
            }
        }
    }
    return ;
}

ostream& operator<<(ostream& out, const List& L){
    LinkNode *cur = L.first->next;
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
